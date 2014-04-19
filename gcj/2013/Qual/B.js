#!/usr/bin/env node
'use strict';
var fs = require('fs');

var lines = fs.readFileSync('/dev/stdin').toString().split(/\n/);
var T = parseInt(lines.shift(), 10);

for (var Ti = 1; Ti <= T; Ti++) {
  var nm = lines.shift().split(/ +/).map(function(x) { return parseInt(x, 10); });
  var n = nm[0];
  var a = [];
  for (var i = 0; i < n; i++) {
    a.push(lines.shift().split(/ +/).map(function(x) { return parseInt(x, 10); }));
  }

  console.log("Case #" + Ti + ": " + (solve(a) ? "YES" : "NO"));
}

function solve(a) {
  var n = a.length, m = a[0].length;
  for (var i = 0; i < n; i++) {
    for (var j = 0; j < m; j++) {
      if (!check(a, i, j)) {
        return false;
      }
    }
  }
  return true;
}

function check(a, i, j) {
  var n = a.length, m = a[0].length;
  var ok = true;
  for (var k = 0; k < n; k++) {
    if (a[k][j] > a[i][j]) {
      ok = false;
      break;
    }
  }
  if (ok) {
    return true;
  }
  for (var k = 0; k < m; k++) {
    if (a[i][k] > a[i][j]) {
      return false;
    }
  }
  return true;
}
