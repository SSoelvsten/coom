#ifndef COOM_BDD_CPP
#define COOM_BDD_CPP

#include "bdd.h"

#include <memory>

#include <coom/file_stream.h>
#include <coom/reduce.h>

namespace coom {
  __bdd::__bdd() : union_t() { }

  __bdd::__bdd(const node_file &f) : union_t(f) { }
  __bdd::__bdd(const arc_file &f) : union_t(f) { }

  __bdd::__bdd(const __bdd &o) : union_t(o), negate(o.negate) { }

  __bdd::__bdd(const bdd &bdd) : union_t(bdd.file), negate(bdd.negate) { }

  void __bdd::set(const bdd &bdd)
  {
    this -> union_t::set(bdd.file);
    this -> negate = bdd.negate;
  }

  __bdd& __bdd::operator<< (const bdd &bdd)
  {
    this -> set(bdd);
    return *this;
  }

  __bdd& __bdd::operator<< (const arc_file &af)
  {
    this -> union_t::set(af);
    return *this;
  }

  __bdd& __bdd::operator<< (const node_file &nf)
  {
    this -> union_t::set(nf);
    return *this;
  }

  //////////////////////////////////////////////////////////////////////////////
  node_file reduce(const __bdd &maybe_reduced)
  {
    if (!maybe_reduced.has<node_file>()) {
      return reduce(maybe_reduced.get<arc_file>());
    }
    return maybe_reduced.get<node_file>();
  }

  //////////////////////////////////////////////////////////////////////////////
  bdd::bdd(const node_file &f, bool negate) : file(f), negate(negate) { }

  bdd::bdd(const bdd &o) : file(o.file), negate(o.negate) { }

  bdd::bdd(const __bdd &o) : file(reduce(o)), negate(o.negate) { }

  //////////////////////////////////////////////////////////////////////////////
  bdd& bdd::operator= (const bdd &other)
  {
    this -> file = other.file;
    this -> negate = other.negate;
    return *this;
  }

  bdd& bdd::operator= (const __bdd &other)
  {
    // Clean up current node_file before the reduce
    this -> file._file_ptr.reset();

    // Reduce and move the resulting node_file into our own
    this -> file = reduce(other);
    this -> negate = other.negate;
    return *this;
  }

  //////////////////////////////////////////////////////////////////////////////
  bool is_sink(const bdd &bdd, const sink_pred &pred)
  {
    node_stream<> ns(bdd);
    node_t n = ns.pull();

    return is_sink(n) && pred(n.uid);
  }

  label_t min_label(const bdd &bdd)
  {
    return max_label(bdd.file);
  }

  label_t max_label(const bdd &bdd)
  {
    return max_label(bdd.file);
  }
}

#endif // COOM_BDD_CPP