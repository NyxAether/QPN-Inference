#pragma once
class strange_rational
	{
	public:
		strange_rational(void);
		strange_rational(int numerator);
		strange_rational(int numerator, int denumerator);
		strange_rational(const strange_rational& sr);
		virtual ~strange_rational(void);

		int numerator() const;
		int denominator() const;
		double value() const;
		bool operator==(const strange_rational& sr) const;
		strange_rational& operator+=(const strange_rational sr);
		strange_rational operator+(const strange_rational& sr) const;
		bool operator<(const strange_rational& sr)const;
	protected:
		int gcd(int a, int b) const;
	protected:
		int num, denom;
	};

