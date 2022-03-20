#pragma once
#include <string>
class Price4 {
private:
	long unscaled_;
public:
	Price4() = default;
	explicit Price4(long unscaled) : unscaled_(unscaled) {}
	// convert from string
	explicit Price4(const std::string& str);
	long unscaled() const { return unscaled_; } //const "this", can't change the member on which they are called. 
	// convert to string
	std::string to_str() const; 
	bool operator==(const Price4& rhs) const{
		return unscaled() == rhs.unscaled();
	}
	bool operator!=(const Price4& rhs) const {
		return !(*this == rhs);
	}
	bool operator<(const Price4& rhs) const {
		return unscaled() < rhs.unscaled();
	}
	bool operator<=(const Price4& rhs) const {
		return unscaled() <= rhs.unscaled();
	}
	bool operator>( const Price4& rhs) const {
		return unscaled() > rhs.unscaled();
	}
	bool operator>=(const Price4& rhs) const {
		return unscaled() >= rhs.unscaled();
	}
};

