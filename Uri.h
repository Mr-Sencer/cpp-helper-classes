#pragma once

#include <map>

#include <string>

using namespace std;

class Uri {
  protected: bool isWhiteAllSpace(char c) {
    return c == 0x20 || c == 0x09 || c == 0x0a || c == 0x0b || c == 0xc || c == 0x0d;

  }
  bool isNumber(char c) {
    return c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9';
  }
  public: map < string, string > Parameters;
  string connectionMode;
  enum Mode {
    ConnectionMode,
    Host,
    Path,
    Query,
    Fragment
  };
  Mode mode = ConnectionMode;
  string host;
  string port;
  int Port;
  string AbsolutePath;
  string OriginalString;
  string QueryString;
  string PathAndQuery;
  string UserName;
  string _Fragment;
  string Password;
  enum HostType {
    IpAdress,
    Domain,
    None
  };
  HostType htype = None;
  // mode = 0 = http https

  void parseHost(string hoststr) {
    int number = 0;
    int len = hoststr.length();
    bool is_host = false;
    // 0: host 
    //1:userName: 
    //2:Password
    //3 Port 

    int _mode = 0;
    string buf;

    int point_number = 0;
    for (int i = 0; i < len; i++) {

      //192.168.1.4
      if (hoststr[i] == '.') {
        is_host = true;
        point_number++;
        if (point_number > 1) {
          if (isNumber(hoststr[i - 1])) {
            htype = IpAdress;
          }

        } else {
          htype = Domain;
        }

      }
      if (hoststr[i] == ':') {
        if (is_host == true) {
          host = buf;
          buf = "";
        }
        if (isNumber(hoststr[i + 1]) == true && htype != None) {

          for (int n = i + 1; n < len; n++) {
            if (isNumber(hoststr[n]) == true) {
              port += hoststr[n];

            } else {
              i = n - 1;

              break;

            }
          }
          Port = atoi(port.c_str());
          continue;
        }
        number++;
        point_number = 0;
        is_host = false;
      }
      if (hoststr[i] == '@') {

        string query1 = buf;
        string buf1;
        int length = query1.length();
        int __mode = 0;
        for (int i = 0; i < length; i++) {
          if (query1[i] == ':') {
            UserName = buf1;
            __mode = 1;
            buf1 = "";
            continue;
          }

          buf1 += query1[i];
          if (i == length - 1) {
            if (__mode == 1) {
              Password = buf1;
              buf1 = "";

            }

          }

        }
        buf = "";
        continue;
      }
      if (isWhiteAllSpace(hoststr[i]) == false) {
        buf += hoststr[i];

      }

    }
    if (htype != None && htype == Domain) {
      host = buf;
    }
  }
  void parseQuery(string query) {
    int len = query.length();
    string name = "";
    string buf;
    for (int i = 1; i < len; i++) {
      if (query[i] == '=') {
        name = buf;
        buf = "";
        continue;
      }
      if (query[i] == '&' || i == len - 1) {
        Parameters.insert(pair < string, string > (name, buf));
        buf = "";
        name = "";
        continue;
      }
      buf += query[i];

    }
  }
  Uri(string url) {
    Parse(url);
  }
  public: void Parse(string url) {
    int len = url.length();
    OriginalString = url;
    string buf;

    int n = 0;

    for (int i = 0; i < len; i++) {
      if (url[i] == ':' && url[i + 1] == '/' && url[i + 2] == '/') {
        connectionMode = buf;
        buf = "";
        mode = Host;
        i = i + 2;
        continue;

      }

      if (url[i] == '/') {
        if (n == 0) {
          parseHost(buf);
          mode = Path;
          buf = "";
          n++;
          continue;

        }
        n++;

      }
      if (url[i] == '?') {
        AbsolutePath += '/';
        AbsolutePath += buf;
        QueryString += '?';
        buf += url[i];
        mode = Query;
        continue;
      }
      if (url[i] == '#') {
        if (mode == Query) {
          PathAndQuery += '/';
          PathAndQuery += buf;

          parseQuery(QueryString);
        }
        mode = Fragment;
        buf += url[i];
        continue;

      }
      if (isWhiteAllSpace(url[i]) == false) {
        buf += url[i];
        if (mode == Query) {
          QueryString += url[i];

        }
        if (mode == Fragment) {
          _Fragment += url[i];
        }
      }

      if (i == len - 1) {
        if (mode == Query) {
          parseQuery(QueryString);
        }
      }
    }

  }

};
