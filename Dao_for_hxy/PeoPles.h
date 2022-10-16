#pragma once
#include "Configuration.h"

using namespace std;

namespace peoples {
	class BasicPeoPle {
	public:
		BasicPeoPle(int id) : id_(id) {}
	protected:
		int id_;
	};
}