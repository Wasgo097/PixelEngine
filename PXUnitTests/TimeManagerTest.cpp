#include "pch.h"
#include <memory>
#include <thread>
#include <chrono>
#include <gtest/gtest.h>
#include "PXCore/Time/TimeManager.h"
using namespace Core::Time;
using namespace std::chrono_literals;
class TimeManagerTest :public testing::Test {
protected:
	std::unique_ptr<TimeManager> _manager;
public:
	virtual void SetUp()override {
		Reset();
	}
	void Reset(float multipler = 1.0) {
		_manager.reset(new TimeManager(nullptr,Settings::ActorSettings(),Settings::TextureSettings(), multipler));
	}
};
class BaseObserver :public Time::ITimeObserver {
public:
	BaseObserver() :_id{ _next_id } {
		_next_id++;
	}
	~BaseObserver() {
		_next_id--;
	}
	virtual void SecondPassed()override {
		std::cout << "Second passed " << _id << std::endl;
		_value = true;
	}
	virtual void MinutePassed()override {
		std::cout << "Minute passed " << _id << std::endl;
		_value = true;
	}
	std::atomic_bool _value = false;
protected:
	int _id = -1;
	static int _next_id;
};
class BaseObserverForMultipler :public Time::ITimeObserver {
public:
	BaseObserverForMultipler() :_id{ _next_id } {
		_next_id++;
	}
	~BaseObserverForMultipler() {
		_next_id--;
	}
	virtual void SecondPassed()override {
		std::cout << "Second passed on MultiplerObserver" << _id << std::endl;
		if (_counter>0)
			_value = !_value;
		_counter++;
	}
	virtual void MinutePassed()override {
		std::cout << "Minute passed on MultiplerObserver" << _id << std::endl;
		if (_counter > 0)
			_value = !_value;
		_counter++;
	}
	std::atomic_bool _value = false;
protected:
	int _id = -1;
	int _counter = 0;
	static int _next_id;
};
int BaseObserver::_next_id = 0;
int BaseObserverForMultipler::_next_id = 0;
TEST_F(TimeManagerTest, NotifyBaseObserverWithWaiting1sTest) {
	BaseObserver o1, o2;
	_manager->AttachToSeconds(&o1);
	_manager->AttachToSeconds(&o2);
	std::this_thread::sleep_for(1010ms);
	EXPECT_TRUE(o1._value.load());
	EXPECT_TRUE(o2._value.load());
}
TEST_F(TimeManagerTest, NotifyBaseObserverWithoutWaitingTest) {
	Reset();
	BaseObserver o1, o2;
	_manager->AttachToSeconds(&o1);
	_manager->AttachToSeconds(&o2);
	EXPECT_FALSE(o1._value.load());
	EXPECT_FALSE(o2._value.load());
}
TEST_F(TimeManagerTest, NotifyBaseObserverWithWaiting500msTest) {
	Reset();
	BaseObserver o1, o2;
	_manager->AttachToSeconds(&o1);
	_manager->AttachToSeconds(&o2);
	std::this_thread::sleep_for(510ms);
	EXPECT_FALSE(o1._value.load());
	EXPECT_FALSE(o2._value.load());
}
TEST_F(TimeManagerTest, NotifyBaseObserverWithWaiting500msAndMultiplerTest) {
	Reset(2.0f);
	BaseObserver o1, o2;
	_manager->AttachToSeconds(&o1);
	_manager->AttachToSeconds(&o2);
	std::this_thread::sleep_for(510ms);
	EXPECT_TRUE(o1._value.load());
	EXPECT_TRUE(o2._value.load());
}
TEST_F(TimeManagerTest, NotifyBaseObserverWithWaiting1sAndMultiplerMinutesTest) {
	Reset(60.0f);
	BaseObserver o1, o2;
	_manager->AttachToMinutes(&o1);
	_manager->AttachToMinutes(&o2);
	std::this_thread::sleep_for(1010ms);
	EXPECT_TRUE(o1._value.load());
	EXPECT_TRUE(o2._value.load());
}
//
TEST_F(TimeManagerTest, NotifyMultiplerObserverWithWaiting1sTest) {
	Reset(2.0f);
	BaseObserverForMultipler o1, o2;
	_manager->AttachToSeconds(&o1);
	_manager->AttachToSeconds(&o2);
	std::this_thread::sleep_for(1010ms);
	EXPECT_TRUE(o1._value.load());
	EXPECT_TRUE(o2._value.load());
}
TEST_F(TimeManagerTest, NotifyMultiplerObserverWithoutWaitingTest) {
	Reset(2.0f);
	BaseObserverForMultipler o1, o2;
	_manager->AttachToSeconds(&o1);
	_manager->AttachToSeconds(&o2);
	EXPECT_FALSE(o1._value.load());
	EXPECT_FALSE(o2._value.load());
}
TEST_F(TimeManagerTest, NotifyMultiplerObserverWithWaiting500msTest) {
	Reset(2.0f);
	BaseObserverForMultipler o1, o2;
	_manager->AttachToSeconds(&o1);
	_manager->AttachToSeconds(&o2);
	std::this_thread::sleep_for(510ms);
	EXPECT_FALSE(o1._value.load());
	EXPECT_FALSE(o2._value.load());
}