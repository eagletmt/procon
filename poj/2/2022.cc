#include <iostream>
#include <sstream>
#include <iterator>
using namespace std;

typedef string::const_iterator Iterator;

bool literal(Iterator& it, const Iterator& last, const string& s)
{
  if (distance(it, last) < s.size()) { return false; }
  const string t(it, it+s.size());
  if (t != s) { return false; }
  it += s.size();
  return true;
}

bool text(Iterator& it, const Iterator& last);

bool bold(Iterator& it, const Iterator& last)
{
  const Iterator save = it;
  if (literal(it, last, "<B>") && text(it, last) && literal(it, last, "</B>")) {
    return true;
  } else {
    it = save;
    return false;
  }
}

bool italics(Iterator& it, const Iterator& last)
{
  const Iterator save = it;
  if (literal(it, last, "<I>") && text(it, last) && literal(it, last, "</I>")) {
    return true;
  } else {
    it = save;
    return false;
  }
}

bool url(Iterator& it, const Iterator& last)
{
  const Iterator save = it;
  if (!literal(it, last, "http://")) {
    return false;
  }
  if (*it == '<' || *it == '>') {
    it = save;
    return false;
  }
  while (it != last && *it != '<' && *it != '>') {
    ++it;
  }
  const string com(it-4, it);
  if (com == ".com") {
    return true;
  } else {
    it = save;
    return false;
  }
}

bool link(Iterator& it, const Iterator& last)
{
  const Iterator save = it;
  if (literal(it, last, "<A HREF=") && url(it, last)
      && literal(it, last, ">") && text(it, last) && literal(it, last, "</A>")) {
    return true;
  } else {
    it = save;
    return false;
  }
}

bool text(Iterator& it, const Iterator& last)
{
  if (it == last) { return false; }
  Iterator jt = it;
  if (*it == '<') {
    if (literal(jt, last, "<B>")) {
      if (!bold(it, last)) { return false; }
    } else if (literal(jt, last, "<I>")) {
      if (!italics(it, last)) { return false; }
    } else if (literal(jt, last, "<A HREF=")) {
      if (!link(it, last)) { return false; }
    }
  } else {
    // strings
    while (it != last && *it != '<' && *it != '>') {
      ++it;
    }
  }

  jt = it;
  while (it != last
      && (literal(jt, last, "<B>") || literal(jt, last, "<I>") || literal(jt, last, "<A HREF=") || (*jt != '<' && *jt != '>'))) {
    if (jt = it, literal(jt, last, "<B>")) {
      if (!bold(it, last)) { return false; }
    } else if (jt = it, literal(jt, last, "<I>")) {
      if (!italics(it, last)) { return false; }
    } else if (jt = it, literal(jt, last, "<A HREF=")) {
      if (!link(it, last)) { return false; }
    } else {
      jt = it;
      while (it != last && *it != '<' && *it != '>') {
        ++it;
      }
      string d(jt, it);
    }
    jt = it;
  }
  return true;
}

bool body(Iterator& it, const Iterator& last)
{
  if (!literal(it, last, "<BODY>")) { return false; }
  if (!text(it, last)) { return false; }
  if (!literal(it, last, "</BODY>")) { return false; }
  return true;
}

bool html_code(Iterator& it, const Iterator& last)
{
  if (!literal(it, last, "<HTML>")) { return false; }
  if (!body(it, last)) { return false; }
  if (!literal(it, last, "</HTML>")) { return false; }
  return true;
}

bool solve(const string& s)
{
  Iterator it = s.begin(), end = s.end();
  if (!html_code(it, end)) {
    return false;
  }
  if (it != end && *it == '\n') {
    ++it;
  }
  return it == end;
}

int main()
{
  string s;
  getline(cin, s);
  istringstream iss(s);
  int n;
  iss >> n;
  while (n-- > 0) {
    getline(cin, s);
    cout << (solve(s) ? "" : "No ") << "Syntax Included" << endl;
  }
  return 0;
}