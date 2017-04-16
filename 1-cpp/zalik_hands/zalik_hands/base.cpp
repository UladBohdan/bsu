#include "base.h"

base::base() : n(0) { }

base::base(int a) : n(a) { }

int base::value() { return n; }

base::~base() { }
