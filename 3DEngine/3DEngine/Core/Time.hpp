#ifndef TuomasSaatana_hpp
#define TuomasSaatana_hpp
#include <chrono>

namespace Engine
{
	typedef double DeltaTime;

	class Time
	{
	public:
		Time();
		~Time();
		void Update();
		DeltaTime GetDeltaTime();
	private:
		std::chrono::time_point<std::chrono::system_clock> _start;
		std::chrono::time_point<std::chrono::system_clock> _end;
	};

	Time::Time() {
		_start = std::chrono::system_clock::now();
	}

	Time::~Time()
	{}

	void Time::Update() {
		_start = _end;
		_end = std::chrono::system_clock::now();
	}

	DeltaTime Time::GetDeltaTime() {
		return std::chrono::duration<double>(_end - _start).count();
	}
}
#endif /*END TIME_H*/