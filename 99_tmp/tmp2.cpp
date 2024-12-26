
class BasicA {
  public:
    int m_i = 0;
    bool m_b = true;
};

class BasicB {
  private:
    BasicA m_ba;
    int m_i;
};

int main() {
    void *pB = nullptr;
    pB = new BasicB;
    BasicA *pA = (BasicA *)pB;
    pA->m_b = 0;
    pA->m_i = 1;
    return 0;
}