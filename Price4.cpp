#include "Price4.h"
#include <sstream>
#include <iomanip>
Price4::Price4(const std::string& str) {
	unscaled_ = std::stol(str);
}

std::string Price4::to_str() const{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << float(unscaled_) * 0.0001;
	return ss.str();
}

/*
bool operator==(const Price4& lhs, const Price4& rhs) {
	return lhs.unscaled() == rhs.unscaled();
}
bool operator!=(const Price4& lhs, const Price4& rhs) {
	return !(lhs == rhs);
}
bool operator<(const Price4& lhs, const Price4& rhs) {
	return lhs.unscaled() < rhs.unscaled();
}
bool operator<=(const Price4& lhs, const Price4& rhs) {
	return lhs.unscaled() <= rhs.unscaled();
}
bool operator>(const Price4& lhs, const Price4& rhs) {
	return lhs.unscaled() > rhs.unscaled();
}
bool operator>=(const Price4& lhs, const Price4& rhs) {
	return lhs.unscaled() >= rhs.unscaled();
}*/
