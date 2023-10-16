#include <iostream>
#include <cmath>
using namespace std;
/*
用面向对象的思维设计相关类。实现直线与直线，直线与圆，直线与矩形的交点。
直线方程采用ay+bx+c的形式。矩形的四条边平行于坐标轴x,y
c++实现
*/
// 直线类
class Line
{
private:
    double a;
    double b;
    double c;

public:
    Line(double a, double b, double c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }
    double getA()
    {
        return a;
    }
    double getB()
    {
        return b;
    }
    double getC()
    {
        return c;
    }
};
class Circal
{
private:
    double o_x;
    double o_y;
    double r;

public:
    Circal(double x, double y, double r)
    {
        o_x = x;
        o_y = y;
        this->r = r;
    }
    double getX()
    {
        return o_x;
    }
    double getY()
    {
        return o_y;
    }
    double getR()
    {
        return r;
    }
};
// 注意x1<x2,y1<y2
class Rec
{
private:
    double x1;
    double x2;
    double y1;
    double y2;

public:
    Rec(double x1, double x2, double y1, double y2)
    {
        this->x1 = x1;
        this->x2 = x2;
        this->y1 = y1;
        this->y2 = y2;
    }
    double getX1()
    {
        return x1;
    }
    double getX2()
    {
        return x2;
    }
    double getY1()
    {
        return y1;
    }
    double getY2()
    {
        return y2;
    }
};
// 直线方程ax+by+c=0,
// k=-a/b
// 两直线平行有k1=k2,即a1b2=a2b1。若重合则c1b2=c2b1。否则相交
void LineAndLine(Line l1, Line l2)
{
    // 斜率相等
    if (l1.getA() * l2.getB() == l2.getA() * l1.getB())
    {
        // 重合
        if (l1.getC() * l2.getB() == l2.getC() * l1.getB())
        {
            cout << "两直线重合，有无数个交点" << endl;
        }
        // 平行但不重合
        else
        {
            cout << "两直线平行,没有交点" << endl;
        }
    }
    // 相交
    else
    {
        if ((l2.getC() * l1.getB() - l1.getC() * l2.getB()) == 0 && (l1.getC() * l2.getA() - l2.getC() * l1.getA()) == 0)
        {
            cout << "交点坐标为(0，0)" << endl;
        }
        else
        {
            cout << "交点坐标为(" << (l2.getC() * l1.getB() - l1.getC() * l2.getB()) / (l1.getA() * l2.getB() - l2.getA() * l1.getB()) << "," << (l1.getC() * l2.getA() - l2.getC() * l1.getA()) / (l1.getA() * l2.getB() - l2.getA() * l1.getB()) << ")" << endl;
        }
    }
}

// 直线和圆的交点
// 根据圆心到直线的距离d与圆半径r的关系判断直线与圆的交点个数
// d>r无交点,
// d=r有一个交点,过圆心做垂直于l的直线。即可转化为直线与直线的交点.两直线垂直k1*k2=-1,A1*A2+B1*B2=0, 1.A2=B1,B2=-A1 2. L2平行于X轴A2=0,L1平行于Y轴B1=0 2.L1平行于X轴A1=0,L2平行于Y轴B2=0. A2*ox+B2*oy+C2=0
// d<r有两个交点
//
void LineAndCir(Line l, Circal o)
{
    double d = fabs(l.getA() * o.getX() + l.getB() * o.getY() + l.getC()) / sqrt(l.getA() * l.getA() + l.getB() * l.getB());

    // 相离
    if (d > o.getR())
    {
        cout << "直线与圆相离，无交点" << endl;
    }
    // 相切
    else if (d == o.getR())
    {
        // 过圆心做垂直于l的直线
        double A2 = l.getB();
         double B2 = -l.getA();
         double C2 = -(A2 * o.getX() + B2 * o.getY());
         Line l2(A2, B2, C2);
        LineAndLine(l, l2);
    }
    // 相交
    else
    {
        double dm = sqrt(o.getR() * o.getR() - d * d);
        double x1, x2, y1, y2;
        // 直线平行于y轴时
        if (l.getB() == 0)
        {
            y1 = o.getY() + dm;
            y2 = o.getY() - dm;
            // 左侧
            if (-l.getC() / l.getA() < o.getX())
                x1 = o.getX() - d;
            else // 右侧
                x1 = o.getX() + d;

            x2 = x1;
        }
        // 直线平行于x轴时
        else if (l.getA() == 0)
        {
            x1 = o.getX() + dm;
            x2 = o.getX() - dm;
            // 下侧
            if (-l.getC() / l.getB() < o.getY())
                y1 = o.getY() - d;
            else // 上侧
                y1 = o.getY() + d;

            y2 = x1;
        }
        // 倾斜直线
        else
        {
            double tan = -l.getA() / l.getB();
            double cos = sqrt(1 / (tan * tan + 1));
            double sin = sqrt(tan * tan / (tan * tan + 1));
            x1 = o.getX() + dm * cos;
            y1 = o.getY() + dm * sin;
            x2 = o.getX() - dm * cos;
            y2 = o.getY() - dm * sin;
        }
        cout << "直线与圆相交，交点1为(" << x1 << "," << y1 << ")，交点2为(" << x2 << "," << y2 << ")" << endl;
    }
}

// 直线与矩形的交点
// 根据代入x1,x2,y1,y2看直线上的点是否在矩形内
// 若是则输出
void LineAndRec(Line l, Rec rec)
{
    // 与长重合
    if (-l.getC() / l.getB() == rec.getY1() || -l.getC() / l.getB() == rec.getY2())
        cout << "直线与矩形的长重合，有无数个交点" << endl;
    // 与宽重合
    else if (-l.getC() / l.getA() == rec.getX1() || -l.getC() / l.getA() == rec.getX2())
        cout << "直线与矩形的宽重合，有无数个交点" << endl;
    else
    {
        double x, y;
        int num = 0;
        bool fy1 = true, fy2 = true, fx1 = true, fx2 = true;
        if (fy1)
        {
            x = (-l.getC() - l.getB() * rec.getY1()) / l.getA();
            if (rec.getX1() <= x && x <= rec.getX2())
                cout << "交点" << ++num << "坐标为(" << x << "," << rec.getY1() << ")" << endl;
            if (x == rec.getX1())
                fx1 = false;
            if (x == rec.getX2())
                fx2 = false;
        }
        if (fy2)
        {
            x = (-l.getC() - l.getB() * rec.getY2()) / l.getA();
            if (rec.getX1() <= x && x <= rec.getX2())
                cout << "交点" << ++num << "坐标为(" << x << "," << rec.getY2() << ")" << endl;
            if (x == rec.getX1())
                fx1 = false;
            if (x == rec.getX2())
                fx2 = false;
        }
        if (fx1)
        {
            y = (-l.getC() - l.getA() * rec.getX1()) / l.getB();
            if (rec.getY1() <= y && y <= rec.getY2())
                cout << "交点" << ++num << "坐标为(" << rec.getX1() << "," << y << ")" << endl;
        }
        if (fx2)
        {
            y = (-l.getC() - l.getA() * rec.getX2()) / l.getB();
            if (rec.getY1() <= y && y <= rec.getY2())
                cout << "交点" << ++num << "坐标为(" << rec.getX2() << "," << y << ")" << endl;
        }
        if (num == 0)
            cout << "直线与矩形没有交点" << endl;
    }
}
int main()
{
    cout << "初始:----------------------------------------------------------------------------------" << endl;
    Line a(1, 1, -4);
    Line b(1, 1, -4);
    Circal o(0, 0, 1);
    Rec rec(1, 2, 1, 2);
    cout << "直线a:" << a.getA() << "x+" << a.getB() << "y"
         << "+" << a.getC() << "=0,直线b:" << b.getA() << "x+" << b.getB() << "y+" << b.getC() << "=0;圆o:圆心为(" << o.getX() << "," << o.getY() << ")，半径为" << o.getR() << ";矩形rec:(" << rec.getX1() << "," << rec.getY1() << "),(" << rec.getX1() << "," << rec.getY2() << "),(" << rec.getX2() << "," << rec.getY2() << "),(" << rec.getX2() << "," << rec.getY1() << ")。" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "直线a与直线b交点:" << endl;
    LineAndLine(a, b);
    cout << "直线a与圆o交点:" << endl;
    LineAndCir(a, o);
    cout << "直线a与矩形rec交点:" << endl;
    LineAndRec(a, rec);
    system("pause");
    return 0;
}