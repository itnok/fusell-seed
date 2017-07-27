#ifndef GASSYFS_ADDRESS_SPACE_H_
#define GASSYFS_ADDRESS_SPACE_H_
#include <cstddef>
#include <vector>

struct gassyfs_opts;

/*
 * A node is a single linearly addressable region that supports random read /
 * write operations (e.g. a GASNet node). The address space exposed by a node
 * is physically located on a single host.
 */
class Node {
 public:
  // valid address space: [0, size)
  virtual size_t size() = 0;

  // synchronous
  virtual void read(void *dst, void *src, size_t len) = 0;
  virtual void write(void *dst, void *src, size_t len) = 0;
};

/*
 * An address space is a set of nodes.
 */
class AddressSpace {
 public:
  virtual std::vector<Node*>& nodes() = 0;
};

class LocalAddressSpace : public AddressSpace {
 public:
  int init(struct filesystem_opts *opts);

  std::vector<Node*>& nodes() {
    return nodes_;
  }

 private:
  std::vector<Node*> nodes_;
};

#endif
