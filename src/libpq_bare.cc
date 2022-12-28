#include <napi.h>
#include <libpq-fe.h>

using namespace Napi;

// nPQconnectdb : string -> conn
Value nPQconnectdb(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }
  if (!info[0].IsString()) {
    Napi::TypeError::New(env, "Wrong arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  std::string dbUrl = info[0].As<Napi::String>().Utf8Value();

  PGconn *conn = PQconnectdb(dbUrl.c_str());

  return External<PGconn>::New(env, conn);
}

// nPQstatus : conn -> integer (see ConnStatusType in libpq)
Value nPQstatus(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsExternal()) {
    Napi::TypeError::New(env, "Wrong arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  External<PGconn> conn = info[0].As<External<PGconn>>();

  ConnStatusType status = PQstatus(conn.Data());

  return Number::New(env, (int)status);
}

// nPQerrorMessage : conn -> string
Value nPQerrorMessage(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsExternal()) {
    Napi::TypeError::New(env, "Wrong arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  External<PGconn> conn = info[0].As<External<PGconn>>();

  char *error = PQerrorMessage(conn.Data());

  return String::New(env, error);
}

// nPQconsumeInput : conn -> integer (boolean)
Value nPQconsumeInput(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsExternal()) {
    Napi::TypeError::New(env, "Wrong arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  External<PGconn> conn = info[0].As<External<PGconn>>();

  int result = PQconsumeInput(conn.Data());

  return Number::New(env, result);
}

// nPQfinish : conn -> ()
Value nPQfinish(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
    return env.Undefined();
  }

  if (!info[0].IsExternal()) {
    Napi::TypeError::New(env, "Wrong arguments")
      .ThrowAsJavaScriptException();
    return env.Undefined();
  }

  External<PGconn> conn = info[0].As<External<PGconn>>();

  PQfinish(conn.Data());

  return env.Undefined();
}

// nPQexec : conn -> string -> result
Value nPQexec(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsExternal() || !info[1].IsString()) {
    Napi::TypeError::New(env, "Wrong arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  External<PGconn> conn = info[0].As<External<PGconn>>();
  std::string command = info[1].As<String>().Utf8Value();

  PGresult *res = PQexec(conn.Data(), command.c_str());

  return External<PGresult>::New(env, res);
}

// nPQclear : result -> ()
Value nPQclear(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
    return env.Undefined();
  }

  if (!info[0].IsExternal()) {
    Napi::TypeError::New(env, "Wrong arguments")
      .ThrowAsJavaScriptException();
    return env.Undefined();
  }

  External<PGresult> res = info[0].As<External<PGresult>>();

  PQclear(res.Data());

  return env.Undefined();
}

// nPQresultStatus : result -> integer (see ExecStatusType enum for libpq)
Value nPQresultStatus(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsExternal()) {
    Napi::TypeError::New(env, "Wrong arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  External<PGresult> res = info[0].As<External<PGresult>>();

  ExecStatusType status = PQresultStatus(res.Data());

  return Number::New(env, (int)status);
}

// nPQresultErrorMessage : result -> string
Value nPQresultErrorMessage(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsExternal()) {
    Napi::TypeError::New(env, "Wrong arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  External<PGresult> res = info[0].As<External<PGresult>>();

  char *error = PQresultErrorMessage(res.Data());

  return String::New(env, error);
}

// nPQntuples : result -> integer
Value nPQntuples(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsExternal()) {
    Napi::TypeError::New(env, "Wrong arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  External<PGresult> res = info[0].As<External<PGresult>>();

  int result = PQntuples(res.Data());

  return Number::New(env, result);
}

// nPQnfields : result -> integer
Value nPQnfields(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsExternal()) {
    Napi::TypeError::New(env, "Wrong arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  External<PGresult> res = info[0].As<External<PGresult>>();

  int result = PQnfields(res.Data());

  return Number::New(env, result);
}

// nPQfname : result -> integer (column) -> string
Value nPQfname(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsExternal() || !info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  External<PGresult> res = info[0].As<External<PGresult>>();
  Number col = info[1].As<Number>();

  char *answer = PQfname(res.Data(), col);

  return String::New(env, answer);
}

// nPQfformat : result -> integer (column) -> integer (postgres format code (text or binary))
Value nPQfformat(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsExternal() || !info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  External<PGresult> res = info[0].As<External<PGresult>>();
  Number col = info[1].As<Number>();

  int answer = PQfformat(res.Data(), col);

  return Number::New(env, answer);
}

// nPQftype : result -> integer (column) -> integer (OID of postgres type)
Value nPQftype(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsExternal() || !info[1].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  External<PGresult> res = info[0].As<External<PGresult>>();
  Number col = info[1].As<Number>();

  int answer = PQftype(res.Data(), col);

  return Number::New(env, answer);
}

// nPQgetisnull : result -> integer (row) -> integer (column) -> integer (bool)
Value nPQgetisnull(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 3) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsExternal() || !info[1].IsNumber() || !info[2].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  External<PGresult> res = info[0].As<External<PGresult>>();
  Number row = info[1].As<Number>();
  Number col = info[2].As<Number>();

  bool answer = PQgetisnull(res.Data(), row, col);

  return Number::New(env, (int)answer);
}

// nPQgetvalue : result -> integer (row) -> integer (column) -> string
Value nPQgetvalue(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 3) {
    Napi::TypeError::New(env, "Wrong number of arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsExternal() || !info[1].IsNumber() || !info[2].IsNumber()) {
    Napi::TypeError::New(env, "Wrong arguments")
      .ThrowAsJavaScriptException();
    return env.Null();
  }

  External<PGresult> res = info[0].As<External<PGresult>>();
  Number row = info[1].As<Number>();
  Number col = info[2].As<Number>();

  char *answer = PQgetvalue(res.Data(), row, col);

  return String::New(env, answer);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(String::New(env, "PQconnectdb"),
              Function::New(env, nPQconnectdb));
  exports.Set(String::New(env, "PQstatus"),
              Function::New(env, nPQstatus));
  exports.Set(String::New(env, "PQexec"),
              Function::New(env, nPQexec));
  exports.Set(String::New(env, "PQclear"),
              Function::New(env, nPQclear));
  exports.Set(String::New(env, "PQresultStatus"),
              Function::New(env, nPQresultStatus));
  exports.Set(String::New(env, "PQresultErrorMessage"),
              Function::New(env, nPQresultErrorMessage));
  exports.Set(String::New(env, "PQntuples"),
              Function::New(env, nPQntuples));
  exports.Set(String::New(env, "PQnfields"),
              Function::New(env, nPQnfields));
  exports.Set(String::New(env, "PQfname"),
              Function::New(env, nPQfname));
  exports.Set(String::New(env, "PQfformat"),
              Function::New(env, nPQfformat));
  exports.Set(String::New(env, "PQftype"),
              Function::New(env, nPQftype));
  exports.Set(String::New(env, "PQgetisnull"),
              Function::New(env, nPQgetisnull));
  exports.Set(String::New(env, "PQgetvalue"),
              Function::New(env, nPQgetvalue));
  exports.Set(String::New(env, "PQerrorMessage"),
              Function::New(env, nPQerrorMessage));
  exports.Set(String::New(env, "PQconsumeInput"),
              Function::New(env, nPQconsumeInput));
  exports.Set(String::New(env, "PQfinish"),
              Function::New(env, nPQfinish));
  return exports;
}

NODE_API_MODULE(addon, Init)
