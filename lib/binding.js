const addon = require('../build/Release/pq-bare-native');

module.exports = {
  PQconnectdb: addon.PQconnectdb,
  PQstatus: addon.PQstatus,
  PQexec: addon.PQexec,
  PQclear: addon.PQclear,
  PQresultStatus: addon.PQresultStatus,
  PQresultErrorMessage: addon.PQresultErrorMessage,
  PQntuples: addon.PQntuples,
  PQnfields: addon.PQnfields,
  PQfname: addon.PQfname,
  PQfformat: addon.PQfformat,
  PQftype: addon.PQftype,
  PQgetisnull: addon.PQgetisnull,
  PQgetvalue: addon.PQgetvalue,
  PQerrorMessage: addon.PQerrorMessage,
  PQconumeInput: addon.PQconsumeInput,
  PQfinish: addon.PQfinish
}

