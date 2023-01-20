#include "Integer.cpp"

template<class T>
bool assert(T r, T l) {
  return r == l ? true : throw std::runtime_error("Test failed");
}

using namespace arbitary_precision_arithmetic;
using namespace std;

class A{};

int main() {
    Integer i1(1000050), i2(11001);

    {
      Integer i((int)1e6);
      i *= i * i * i * i * i * i * i * i * i;
      cout << (int)(uint8_t)i << endl;
    }

    {
      assert((int)i1, 1000050);
      cout << endl <<  "i1 = " << i1 << endl;
      assert((int)i2, 11001);
      cout << "i2 = " << i2 << endl << endl;
    }

    {
      Integer i3 = i1 + i2;
      assert((int64_t)i3, (int64_t)1011051);
      cout << "i1 + i2 = " << i3 << endl << endl;
    }

    {
      Integer i3 = i1 - i2;
      assert((int64_t)i3, (int64_t)989049);
      cout << "i1 - i2 = " << i3 << endl << endl;
    }

    {
      Integer i3 = i2 - i1;
      assert((int64_t)i3, (int64_t)-989049);
      cout << "i2 - i1 = " << i3 << endl << endl;
    }

    {
      Integer i3 = i1 * i2;
      assert((int64_t)i3, (int64_t)11001550050);
      cout << "i1 * i2 = " << i3 << endl << endl;
    }

    {
      Integer i3 = i1 / i2;
      assert((int64_t)i3, (int64_t)90);
      cout << "i1 / i2 = " << i3 << endl << endl;
    }

    {
      Integer i3 = i1 % i2;
      assert((int64_t)i3, (int64_t)9960);
      cout << "i1 % i2 = " << i3 << endl << endl;
    }

    {
      Integer i3 = i2;
      assert((int64_t)i3++, (int64_t)11001);
      //cout << "i2++ = " << i3 << endl << endl;
    }

    {
      Integer i3 = i2;
      assert((int64_t)++i3, (int64_t)11002);
      //cout << "++i2 = " << i3 << endl << endl;
    }

    {
      Integer i3 = i2;
      assert((int64_t)i3--, (int64_t)11001);
      //cout << "i2++ = " << i3 << endl << endl;
    }

    {
      Integer i3 = i2;
      assert((int64_t)--i3, (int64_t)11000);
      //cout << "++i2 = " << i3 << endl << endl;
    }

    {
      Integer i3 = -i2;
      assert((int64_t)i3, (int64_t)-11001);
      cout << "-i2 = " << i3 << endl << endl;
    }

    {
      assert(i1 == i2, false);
      cout << "i1 == i2 = " <<  (i1 == i2 ? "true" : "false") << endl << endl;
    }

    {
      assert(i1 != i2, true);
      cout << "i1 != i2 = " <<  (i1 != i2 ? "true" : "false") << endl << endl;
    }

    {
      assert(i1 > i2, true);
      cout << "i1 > i2 = " <<  (i1 > i2 ? "true" : "false") << endl << endl;
    }

    {
      assert(i1 >= i2, true);
      cout << "i1 >= i2 = " <<  (i1 >= i2 ? "true" : "false") << endl << endl;
    }

    {
      assert(i1 < i2, false);
      cout << "i1 < i2 = " <<  (i1 < i2 ? "true" : "false") << endl << endl;
    }

    {
      assert(i1 <= i2, false);
      cout << "i1 <= i2 = " <<  (i1 <= i2 ? "true" : "false") << endl << endl;
    }
}