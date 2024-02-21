#include <fstream>
#include <iostream>

void WriteFile(std::wfstream &fOut) {
  if (!fOut.is_open())
    return;
  fOut << L"A line English\n";
  fOut << L"窗前明月光\n";
  fOut << L"疑似地上霜\n";
  fOut << L"举头望明月\n";
  fOut << L"低头思故乡";
  fOut.close();
}

int main() {
  using namespace std;

  wfstream wf_not;
  wf_not.open("locale_not.txt", ios_base::out);
  WriteFile(wf_not);

  wfstream wf_yes;
  wf_yes.imbue(locale(""));
  wf_yes.open("locale_yes.txt", ios_base::out);
  WriteFile(wf_yes);

  system("pause");
  return 0;
}
