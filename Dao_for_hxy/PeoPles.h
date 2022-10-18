#pragma once
#include "Configuration.h"

using namespace std;

namespace peoples {
	class BasicPeoPle {
	public:
		BasicPeoPle(int id) : id_(id) {}
		int getId() { return this->id_; }
	protected:
		int id_;
	};
}