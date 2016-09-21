#pragma once

class PerfTimer
{
public:

	PerfTimer();

	void Start();
	double ReadMs() const;
	int ReadTicks() const;

private:
	int	started_at;
	static int freq;
}; 