#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include <stack>

class Quaternion;

enum ComplexKind {CK_COMPLEX_NUMBER, CK_QUATERNION};

class ComplexNumber {
public:
    ComplexNumber() : real(0), iCoef(0) {}
    
    ComplexNumber(double _real, double _iCoef) : 
        real(_real), iCoef(_iCoef) {}
    
    ComplexNumber(const ComplexNumber& other) : 
        real(other.real), iCoef(other.iCoef) {}

    virtual ~ComplexNumber() {}

    virtual ComplexKind getKind() const {
        return CK_COMPLEX_NUMBER;
    }

    virtual void show() const {
        std::cout << real << " + " << iCoef << "i" << std::endl;
    }

    double getReal() const {
        return real;
    }

    double getI() const {
        return iCoef;
    }
    
    void setReal(double _real) {
        real = _real;
    }

    void setI(double _iCoef) {
        iCoef = _iCoef;
    }

    virtual void setImaginary(const std::vector<double>& imagPart) {
        if (imagPart.size() > 1) {
            std::cout << "Expected one imaginary coefficient, but got " <<
                imagPart.size() << std::endl;
            return;
        }
        iCoef = imagPart[0];
    }

    bool operator== (const ComplexNumber &obj) const {
        if (
            real == obj.real &&
            iCoef == obj.iCoef
        ) return true;
        return false;
    }

    bool operator== (const Quaternion &obj) const;

    bool operator== (double num) const {
        if (
            real == num &&
            iCoef == 0
        ) return true;
        return false;
    }

    ComplexNumber operator+= (const ComplexNumber &obj) {
        real += obj.real;
        iCoef += obj.iCoef;
        return *this;
    }

    ComplexNumber operator+= (double num) {
        real += num;
        return *this;
    }

    ComplexNumber operator+ (const ComplexNumber &obj) const {
        ComplexNumber tmp(*this);
        tmp += obj;
        return tmp;
    }

    Quaternion operator+ (const Quaternion &obj) const;

    ComplexNumber operator+ (double num) const {
        ComplexNumber tmp(*this);
        tmp += num;
        return tmp;
    }

    ComplexNumber operator-= (const ComplexNumber &obj) {
        real -= obj.real;
        iCoef -= obj.iCoef;
        return *this;
    }

    ComplexNumber operator-= (double num) {
        real -= num;
        return *this;
    }

    ComplexNumber operator- (const ComplexNumber &obj) const {
        ComplexNumber tmp(*this);
        tmp -= obj;
        return tmp;
    }

    Quaternion operator- (const Quaternion &obj) const;

    ComplexNumber operator- (double num) {
        ComplexNumber tmp(*this);
        tmp -= num;
        return tmp;
    }

    ComplexNumber operator= (const ComplexNumber &obj) {
        real = obj.real;
        iCoef = obj.iCoef;
        return *this;
    }

    ComplexNumber operator= (double num) {
        real = num;
        iCoef = 0;
        return *this;
    }

    ComplexNumber operator*= (const ComplexNumber &obj) {
        double realRes = real * obj.real - iCoef * obj.iCoef;
        double iCoefRes = real * obj.iCoef + iCoef * obj.real;
        real = realRes;
        iCoef = iCoefRes;
        return *this;
    }

    ComplexNumber operator*= (double num) {
        real *= num;
        iCoef *= num;
        return *this;
    }

    ComplexNumber operator* (const ComplexNumber &obj) const {
        ComplexNumber tmp(*this);
        tmp *= obj;
        return tmp;
    }

    Quaternion operator* (const Quaternion &obj) const;

    ComplexNumber operator* (double num) const {
        ComplexNumber tmp(*this);
        tmp *= num;
        return tmp;
    }

    ComplexNumber operator/= (const ComplexNumber &obj) {
        double realRes = (real * obj.real + iCoef * obj.iCoef) / 
            (std::pow(obj.real, 2) + std::pow(obj.iCoef, 2));
        double iCoefRes = (obj.real * iCoef - obj.iCoef * real) / 
            (std::pow(obj.real, 2) + std::pow(obj.iCoef, 2));
        real = realRes;
        iCoef = iCoefRes;
        return *this;
    }

    ComplexNumber operator/= (double num) {
        real /= num;
        iCoef /= num;
        return *this;
    }

    ComplexNumber operator/ (const ComplexNumber &obj) const {
        ComplexNumber tmp(*this);
        tmp /= obj;
        return tmp;
    }

    Quaternion operator/ (const Quaternion &obj) const;

    ComplexNumber operator/ (double num) const {
        ComplexNumber tmp(*this);
        tmp /= num;
        return tmp;
    }
protected: // вроде не обязательно private
    double real;
    double iCoef;
};

class Quaternion : public ComplexNumber {
public:
    Quaternion() : ComplexNumber(), jCoef(0), kCoef(0) {}

    Quaternion(double _real, double _iCoef, double _jCoef, double _kCoef) :
        ComplexNumber(_real, _iCoef), jCoef(_jCoef), kCoef(_kCoef) {}

    Quaternion(const ComplexNumber& other) :
        ComplexNumber(other),
        jCoef(0),
        kCoef(0) {}

    Quaternion(const Quaternion& other) :
        ComplexNumber((ComplexNumber)other),
        jCoef(other.jCoef),
        kCoef(other.kCoef) {}

    ~Quaternion() override {}

    ComplexKind getKind() const override {
        return CK_QUATERNION;
    }

    void show() const override {
        std::cout << getReal() << " + " << getI() << "i + " <<
            jCoef << "j + " << kCoef << "k" << std::endl;
    }

    double getJ() const {
        return jCoef;
    }

    double getK() const {
        return kCoef;
    }

    void setJ(double _jCoef) {
        jCoef = _jCoef;
    }
    
    void setK(double _kCoef) {
        kCoef = _kCoef;
    }

    void setImaginary(const std::vector<double>& imagPart) override {
        if (imagPart.size() != 3) {
            std::cout << 
            "Expected three imaginary coefficients, but got " << 
            imagPart.size() << std::endl;
            return;
        }
        iCoef = imagPart[0];
        jCoef = imagPart[1];
        kCoef = imagPart[2];
    }

    bool operator== (const Quaternion &obj) const {
        if (
            real == obj.real &&
            iCoef == obj.iCoef &&
            jCoef == obj.jCoef &&
            kCoef == obj.kCoef
        ) return true;
        return false;
    }
    
    bool operator== (const ComplexNumber &obj) const {
        if (
            real == obj.getReal() &&
            iCoef == obj.getI() &&
            jCoef == 0 &&
            kCoef == 0
        ) return true;
        return false;
    }

    bool operator== (double num) const {
        if (
            real == num &&
            iCoef == 0 &&
            jCoef == 0 &&
            kCoef == 0
        ) return true;
        return false;
    }

    Quaternion operator+= (const Quaternion &obj) {
        real += obj.real;
        iCoef += obj.iCoef;
        jCoef += obj.jCoef;
        kCoef += obj.kCoef;
        return *this;
    }

    Quaternion operator+= (const ComplexNumber &obj) {
        real += obj.getReal();
        iCoef += obj.getI();
        return *this;
    }

    Quaternion operator+= (double num) {
        real += num;
        return *this;
    }

    Quaternion operator+ (const ComplexNumber &obj) const {
        Quaternion tmp(*this);
        tmp += obj;
        return tmp;
    }

    Quaternion operator+ (const Quaternion &obj) const {
        Quaternion tmp(*this);
        tmp += obj;
        return tmp;
    }

    Quaternion operator+ (double num) const {
        Quaternion tmp(*this);
        tmp += num;
        return tmp;
    }

    Quaternion operator-= (const Quaternion &obj) {
        real -= obj.real;
        iCoef -= obj.iCoef;
        jCoef -= obj.jCoef;
        kCoef -= obj.kCoef;
        return *this;
    }

    Quaternion operator-= (const ComplexNumber &obj) {
        real -= obj.getReal();
        iCoef -= obj.getI();
        return *this;
    }

    Quaternion operator-= (double num) {
        real -= num;
        return *this;
    }

    Quaternion operator- (const Quaternion &obj) const {
        Quaternion tmp(*this);
        tmp -= obj;
        return tmp;
    }

    Quaternion operator- (const ComplexNumber &obj) const {
        Quaternion tmp(*this);
        tmp -= obj;
        return tmp;
    }

    Quaternion operator- (double num) const {
        Quaternion tmp(*this);
        tmp -= num;
        return tmp;
    }

    Quaternion operator= (const Quaternion &obj) {
        real = obj.real;
        iCoef = obj.iCoef;
        jCoef = obj.jCoef;
        kCoef = obj.kCoef;
        return *this;
    }

    Quaternion operator= (const ComplexNumber &obj) {
        real = obj.getReal();
        iCoef = obj.getI();
        jCoef = 0;
        kCoef = 0;
        return *this;
    }

    Quaternion operator= (double num) {
        real = num;
        iCoef = 0;
        jCoef = 0;
        kCoef = 0;
        return *this;
    }

    Quaternion operator*= (const Quaternion &obj) {
        double realRes = real * obj.real - iCoef * obj.iCoef -
            jCoef * obj.jCoef - kCoef * obj.kCoef;
        double iCoefRes = real * obj.iCoef + iCoef * obj.real +
            jCoef * obj.kCoef - kCoef * obj.jCoef;
        double jCoefRes = real * obj.jCoef - iCoef * obj.kCoef +
            jCoef * obj.real + kCoef * obj.iCoef;
        double kCoefRes = real * obj.kCoef + iCoef * obj.jCoef -
            jCoef * obj.iCoef + kCoef * obj.real;
        real = realRes;
        iCoef = iCoefRes;
        jCoef = jCoefRes;
        kCoef = kCoefRes;
        return *this;
    }

    Quaternion operator*= (const ComplexNumber &obj) {
        double realRes = real * obj.getReal() - iCoef * obj.getI();
        double iCoefRes = real * obj.getI() + iCoef * obj.getReal();
        double jCoefRes = jCoef * obj.getReal() + kCoef * obj.getI();
        double kCoefRes = -jCoef * obj.getI() + kCoef * obj.getReal();
        real = realRes;
        iCoef = iCoefRes;
        jCoef = jCoefRes;
        kCoef = kCoefRes;
        return *this;
    }

    Quaternion operator*= (double num) {
        real *= num;
        iCoef *= num;
        jCoef *= num;
        kCoef *= num;
        return *this;
    }

    Quaternion operator* (const Quaternion &obj) const {
        Quaternion tmp(*this);
        tmp *= obj;
        return tmp;
    }

    Quaternion operator* (const ComplexNumber &obj) const {
        Quaternion tmp(*this);
        tmp *= obj;
        return tmp;
    }

    Quaternion operator* (double num) const {
        Quaternion tmp(*this);
        tmp *= num;
        return tmp;
    }

    Quaternion operator/= (const Quaternion &obj) {
        Quaternion reverse(obj.real, -obj.iCoef, -obj.jCoef, -obj.kCoef);
        reverse /= (std::pow(obj.real, 2) + std::pow(obj.iCoef, 2) +
                std::pow(obj.jCoef, 2) + std::pow(obj.kCoef, 2));
        *this *= reverse;
        return *this;
    }

    Quaternion operator/= (const ComplexNumber &obj) {
        Quaternion reverse(obj.getReal(), -obj.getI(), 0, 0);
        reverse /= (std::pow(obj.getReal(), 2) + std::pow(obj.getI(), 2));
        *this *= reverse;
        return *this;
    }

    Quaternion operator/= (double num) {
        real /= num;
        iCoef /= num;
        jCoef /= num;
        kCoef /= num;
        return *this;
    }

    Quaternion operator/ (const Quaternion &obj) const {
        Quaternion tmp(*this);
        tmp /= obj;
        return tmp;
    }

    Quaternion operator/ (const ComplexNumber &obj) const {
        Quaternion tmp(*this);
        tmp /= obj;
        return tmp;
    }

    Quaternion operator/ (double num) const {
        Quaternion tmp(*this);
        tmp /= num;
        return tmp;
    }
private:
    double jCoef;
    double kCoef;
};

bool ComplexNumber::operator== (const Quaternion &obj) const {
        if (
            real == obj.getReal() &&
            iCoef == obj.getI() &&
            obj.getJ() == 0 &&
            obj.getK() == 0
        ) return true;
        return false;
    }

Quaternion ComplexNumber::operator+ (const Quaternion &obj) const {
    Quaternion tmp(*this);
    tmp += obj;
    return tmp;
}

Quaternion ComplexNumber::operator* (const Quaternion &obj) const {
    Quaternion tmp(*this);
    tmp *= obj;
    return tmp;
}

Quaternion ComplexNumber::operator- (const Quaternion &obj) const {
    Quaternion tmp(*this);
    tmp -= obj;
    return tmp;
}

Quaternion ComplexNumber::operator/ (const Quaternion &obj) const {
    Quaternion tmp(*this);
    tmp /= obj;
    return tmp;
}

enum Operations {OP_ADD, OP_SUBTRACT, OP_MULTIPLY, OP_DIVIDE};

class Calculator {
public:
    Calculator() {
        numbers = std::stack<ComplexNumber*>();
    }

    Calculator(const std::stack<ComplexNumber*>& stack) {
        numbers = stack;
    }

    Calculator(const Calculator& other) {
        numbers = other.numbers;
    }

    ~Calculator() {
        while (numbersToDel.size() > 0) {
            ComplexNumber* toDel = numbersToDel.top();
            numbersToDel.pop();
            delete toDel;
        }
        std::cout << "new items deleted" << std::endl;
    }

    void push(ComplexNumber& number) {
        numbers.push(&number);
    }

    ComplexNumber* top() const {
        return numbers.top();
    }

    int size() const {
        return numbers.size();
    }

    void calculate(Operations operation) {
        if (numbers.size() == 0) {
            std::cout << "the stack is empty" << std::endl;
            return;
        }
        if (numbers.size() == 1) {
            std::cout << "only one operand in stack" << std::endl;
            return;
        }
        ComplexNumber* lOperand = top();
        numbers.pop();
        ComplexNumber* rOperand = top();
        numbers.pop();
        bool isQuaternion = (lOperand->getKind() == CK_QUATERNION ||
            rOperand->getKind() == CK_QUATERNION);
        switch (operation) {
        case OP_ADD:
            if (isQuaternion) {
                Quaternion* res = new Quaternion;
                *res = *(Quaternion*)lOperand + *(Quaternion*)rOperand;
                pushNew(*res);
            } else {
                ComplexNumber* res = new ComplexNumber;
                *res = *lOperand + *rOperand;
                pushNew(*res);
            }
            break;
        case OP_SUBTRACT:
            if (isQuaternion) {
                Quaternion* res = new Quaternion;
                *res = *(Quaternion*)lOperand - *(Quaternion*)rOperand;
                pushNew(*res);
            } else {
                ComplexNumber* res = new ComplexNumber;
                *res = *lOperand - *rOperand;
                pushNew(*res);
            }
            break;
        case OP_MULTIPLY:
            if (isQuaternion) {
                Quaternion* res = new Quaternion;
                *res = *(Quaternion*)lOperand * *(Quaternion*)rOperand;
                pushNew(*res);
            } else {
                ComplexNumber* res = new ComplexNumber;
                *res = *lOperand * *rOperand;
                pushNew(*res);
            }
            break;
        case OP_DIVIDE:
            if (*rOperand == 0) {
                std::cout << "can't divide by 0" << std::endl;
                push(*rOperand);
                push(*lOperand);
                return;
            }
            if (isQuaternion) {
                Quaternion* res = new Quaternion;
                *res = *(Quaternion*)lOperand / *(Quaternion*)rOperand;
                pushNew(*res);
            } else {
                ComplexNumber* res = new ComplexNumber;
                *res = *lOperand / *rOperand;
                pushNew(*res);
            }
            break;
        }
    }
private:
    std::stack<ComplexNumber*> numbers;
    std::stack<ComplexNumber*> numbersToDel;

    void pushNew(ComplexNumber& num) {
        push(num);
        numbersToDel.push(&num);
    }
};

int main() {
    ComplexNumber a;
    assert(a.getReal() == 0);
    assert(a.getI() == 0);
    ComplexNumber b(1, 2);
    assert(b.getReal() == 1);
    assert(b.getI() == 2);
    ComplexNumber c(b);
    assert(c.getReal() == 1);
    assert(c.getI() == 2);
    c.setI(5);
    c.setReal(4);
    assert(c.getReal() == 4);
    assert(c.getI() == 5);
    c.setImaginary({6});
    assert(c.getI() == 6);
    
    Quaternion qu1;
    assert(qu1.getReal() == 0);
    assert(qu1.getI() == 0);
    assert(qu1.getJ() == 0);
    assert(qu1.getK() == 0);
    Quaternion qu2(1, -2, 3, -4);
    Quaternion qu3(qu2);

    assert(qu2.getReal() == 1);
    assert(qu2.getI() == -2);
    assert(qu2.getJ() == 3);
    assert(qu2.getK() == -4);
    assert(qu2.getReal() == qu3.getReal());
    assert(qu2.getI() == qu3.getI());
    qu1.setReal(1);
    assert(qu1.getReal() == 1);
    qu1.setI(10);
    qu1.setJ(11);
    qu1.setK(12);
    assert(qu1.getI() == 10);
    assert(qu1.getJ() == 11);
    assert(qu1.getK() == 12);
    qu1.setImaginary({1, 5, 9});
    assert(qu1.getI() == 1);
    assert(qu1.getJ() == 5);
    assert(qu1.getK() == 9);
    assert(a.getKind() == CK_COMPLEX_NUMBER);
    assert(qu1.getKind() == CK_QUATERNION);
    ComplexNumber* temp = &qu1;
    assert(temp->getKind() == CK_QUATERNION);

    ComplexNumber c1(2, 3);
    ComplexNumber c2(4, 5);
    ComplexNumber c3(2, 3);
    ComplexNumber c4(0, 0);

    assert(c1 == c3);
    assert(!(c1 == c2));
    assert(c4 == 0);
    assert(!(c1 == c4));

    ComplexNumber c5 = c1 + c2;
    assert(c5 == ComplexNumber(6, 8));
    ComplexNumber c6 = c1 + 2;
    assert(c6 == ComplexNumber(4, 3));

    ComplexNumber c7 = c1 - c2;
    assert(c7 == ComplexNumber(-2, -2));
    ComplexNumber c8 = c1 - 2;
    assert(c8 == ComplexNumber(0, 3));

    ComplexNumber c9 = c1 * c2;
    assert(c9 == ComplexNumber(-7, 22));
    ComplexNumber c10 = c1 * 2;
    assert(c10 == ComplexNumber(4, 6));

    ComplexNumber c11 = c1 / c2;
    assert(roundf(c11.getReal()) == roundf(0.561));
    assert(roundf(c11.getI()) == roundf(0.049));
    ComplexNumber c12 = c1 / 2;
    assert(c12 == ComplexNumber(1, 1.5));

    Quaternion q1(1, 2, 3, 4);
    Quaternion q2(1, 2, 3, 4);
    Quaternion q3(1, 2, 3, 0);
    Quaternion q4(1, 2, 0, 0);

    assert(q1 == q2);
    assert(!(q1 == q3));
    assert(q4 == ComplexNumber(1, 2));
    assert(!(q1 == q4));

    Quaternion q5 = q1 + q2;
    assert(q5 == Quaternion(2, 4, 6, 8));
    Quaternion q6 = q1 + c1;
    assert(q6 == Quaternion(3, 5, 3, 4));
    Quaternion q7 = q1 + 2;
    assert(q7 == Quaternion(3, 2, 3, 4));

    Quaternion q8 = q1 - q2;
    assert(q8 == Quaternion(0, 0, 0, 0));
    Quaternion q9 = q1 - c1;
    assert(q9 == Quaternion(-1, -1, 3, 4));
    Quaternion q10 = q1 - 2;
    assert(q10 == Quaternion(-1, 2, 3, 4));

    Quaternion q11 = q1 * q2;
    assert(q11 == Quaternion(-28, 4, 6, 8));
    Quaternion q12 = q1 * c1;
    assert(q12 == Quaternion(-4, 7, 18, -1));
    Quaternion q13 = q1 * 2;
    assert(q13 == Quaternion(2, 4, 6, 8));

    Quaternion q14 = q1 / q2;
    assert(roundf(q14.getReal()) == 1);
    assert(roundf(q14.getI()) == 0);
    assert(roundf(q14.getJ()) == 0);
    assert(roundf(q14.getK()) == 0);
    Quaternion q15 = q1 / c1;
    assert(roundf(q15.getReal()) == roundf(0.615));
    assert(roundf(q15.getI()) == roundf(0.077));
    assert(roundf(q15.getJ()) == roundf(-0.462));
    assert(roundf(q15.getK()) == roundf(1.308));
    Quaternion q16 = q1 / 2;
    assert(q16 == Quaternion(0.5, 1, 1.5, 2));
    
    Calculator calculator;
    calculator.push(c1);
    assert(calculator.top() == &c1);
    calculator.push(c2);
    assert(calculator.size() == 2);
    assert(calculator.top() == &c2);
    std::stack<ComplexNumber*> numStack;
    numStack.push(&c2);
    numStack.push(&c1);
    Calculator calculator2(numStack);
    assert(calculator2.size() == 2);
    assert(calculator2.top() == numStack.top());
    Calculator calculatorCopy(calculator2);
    assert(calculatorCopy.top() == calculator2.top());
    assert(calculatorCopy.size() == calculator2.size());
    calculatorCopy.calculate(OP_ADD);
    calculator2.calculate(OP_ADD);
    assert(*calculatorCopy.top() == *calculator2.top());
    assert(calculatorCopy.size() == calculator2.size());

    calculator.calculate(OP_ADD);
    assert(calculator.size() == 1);
    ComplexNumber* resultAddCC = calculator.top();
    assert(resultAddCC->getKind() == CK_COMPLEX_NUMBER);
    assert(*resultAddCC == c1 + c2);
    calculator.push(q1);
    calculator.calculate(OP_ADD);
    assert(calculator.size() == 1);
    ComplexNumber* resultAddQC = calculator.top();
    assert(resultAddQC->getKind() == CK_QUATERNION);
    assert(*(Quaternion*)resultAddQC == q1 + *(Quaternion*)resultAddCC);
    calculator.push(c2);
    calculator.calculate(OP_ADD);
    assert(calculator.size() == 1);
    ComplexNumber* resultAddCQ = calculator.top();
    assert(resultAddCQ->getKind() == CK_QUATERNION);
    assert(*(Quaternion*)resultAddCQ == c2 + *(Quaternion*)resultAddQC);
    calculator.push(q2);
    calculator.calculate(OP_ADD);
    assert(calculator.size() == 1);
    ComplexNumber* resultAddQQ = calculator.top();
    assert(resultAddQQ->getKind() == CK_QUATERNION);
    assert(*(Quaternion*)resultAddQQ == q2 + *(Quaternion*)resultAddCQ);

    calculator.push(c2);
    calculator.push(c1);
    calculator.calculate(OP_SUBTRACT);
    assert(calculator.size() == 2);
    ComplexNumber* resultSubtractCC = calculator.top();
    assert(resultSubtractCC->getKind() == CK_COMPLEX_NUMBER);
    assert(*resultSubtractCC == c1 - c2);
    calculator.push(q1);
    calculator.calculate(OP_SUBTRACT);
    assert(calculator.size() == 2);
    ComplexNumber* resultSubtractQC = calculator.top();
    assert(resultSubtractQC->getKind() == CK_QUATERNION);
    assert(*(Quaternion*)resultSubtractQC ==
        q1 - *(Quaternion*)resultSubtractCC);
    calculator.push(c2);
    calculator.calculate(OP_SUBTRACT);
    assert(calculator.size() == 2);
    ComplexNumber* resultSubtractCQ = calculator.top();
    assert(resultSubtractCQ->getKind() == CK_QUATERNION);
    assert(*(Quaternion*)resultSubtractCQ ==
        c2 - *(Quaternion*)resultSubtractQC);
    calculator.push(q2);
    calculator.calculate(OP_SUBTRACT);
    assert(calculator.size() == 2);
    ComplexNumber* resultSubtractQQ = calculator.top();
    assert(resultSubtractQQ->getKind() == CK_QUATERNION);
    assert(*(Quaternion*)resultSubtractQQ ==
        q2 - *(Quaternion*)resultSubtractCQ);

    calculator.push(c2);
    calculator.push(c1);
    calculator.calculate(OP_MULTIPLY);
    assert(calculator.size() == 3);
    ComplexNumber* resultMultiplyCC = calculator.top();
    assert(resultMultiplyCC->getKind() == CK_COMPLEX_NUMBER);
    assert(*resultMultiplyCC == c1 * c2);
    calculator.push(q1);
    calculator.calculate(OP_MULTIPLY);
    assert(calculator.size() == 3);
    ComplexNumber* resultMultiplyQC = calculator.top();
    assert(resultMultiplyQC->getKind() == CK_QUATERNION);
    assert(*(Quaternion*)resultMultiplyQC ==
        q1 * *(Quaternion*)resultMultiplyCC);
    calculator.push(c2);
    calculator.calculate(OP_MULTIPLY);
    assert(calculator.size() == 3);
    ComplexNumber* resultMultiplyCQ = calculator.top();
    assert(resultMultiplyCQ->getKind() == CK_QUATERNION);
    assert(*(Quaternion*)resultMultiplyCQ ==
        c2 * *(Quaternion*)resultMultiplyQC);
    calculator.push(q2);
    calculator.calculate(OP_MULTIPLY);
    assert(calculator.size() == 3);
    ComplexNumber* resultMultiplyQQ = calculator.top();
    assert(resultMultiplyQQ->getKind() == CK_QUATERNION);
    assert(*(Quaternion*)resultMultiplyQQ ==
        q2 * *(Quaternion*)resultMultiplyCQ);

    calculator.push(c2);
    calculator.push(c1);
    calculator.calculate(OP_DIVIDE);
    assert(calculator.size() == 4);
    ComplexNumber* resultDivideCC = calculator.top();
    assert(resultDivideCC->getKind() == CK_COMPLEX_NUMBER);
    assert(*resultDivideCC == c1 / c2);
    calculator.push(q1);
    calculator.calculate(OP_DIVIDE);
    assert(calculator.size() == 4);
    ComplexNumber* resultDivideQC = calculator.top();
    assert(resultDivideQC->getKind() == CK_QUATERNION);
    assert(*(Quaternion*)resultDivideQC == q1 / *(Quaternion*)resultDivideCC);
    calculator.push(c2);
    calculator.calculate(OP_DIVIDE);
    assert(calculator.size() == 4);
    ComplexNumber* resultDivideCQ = calculator.top();
    assert(resultDivideCQ->getKind() == CK_QUATERNION);
    assert(*(Quaternion*)resultDivideCQ == c2 / *(Quaternion*)resultDivideQC);
    calculator.push(q2);
    calculator.calculate(OP_DIVIDE);
    assert(calculator.size() == 4);
    ComplexNumber* resultDivideQQ = calculator.top();
    assert(resultDivideQQ->getKind() == CK_QUATERNION);
    assert(*(Quaternion*)resultDivideQQ == q2 / *(Quaternion*)resultDivideCQ);
    c1 = 0;
    q1 = 0;
    calculator.push(c1);
    calculator.push(c2);
    calculator.calculate(OP_DIVIDE);
    assert(calculator.size() == 6);
    calculator.push(q1);
    calculator.push(c2);
    calculator.calculate(OP_DIVIDE);
    assert(calculator.size() == 8);
    calculator.push(c1);
    calculator.push(q2);
    calculator.calculate(OP_DIVIDE);
    assert(calculator.size() == 10);
    calculator.push(q1);
    calculator.push(q2);
    calculator.calculate(OP_DIVIDE);
    assert(calculator.size() == 12);

    std::cout << "All tests passed!" << std::endl;
    
    return 0;
}
