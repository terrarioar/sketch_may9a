class Motor {
public:
	bool dir = 0;
	int times = 0;

	Motor();
	Motor(int in, int out);
	~Motor();
	void setStatus(bool d, int times);
	void move();

private:
	int inpin,outpin;
};
