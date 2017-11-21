var round = 0;

function start() {
  document.getElementById("startBtn").className = "no-display"
  processResponse(httpGet("/next/"))
}

function httpGet(theUrl) {
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", theUrl, false);
    xmlHttp.send(null);
    return xmlHttp.responseText;
}

function appendQuestion(prompt) {
  var e = document.createElement('div');
  e.className = "question-div"
  e.innerHTML = `<div class="question title is-3">${prompt.Question}</div>`
  for (i in prompt.Answers) {
    var idName = round + "_" + i;
    e.innerHTML += `<a onclick="answer(${i})" class="btn button" id="${idName}">${prompt.Answers[i]}</a>`
  }

  document.getElementById("questions").appendChild(e)
}

function answer(i) {
  document.getElementById(round + "_" + i).className += " is-warning";
  round++;
  processResponse(httpGet("/next/" + i + "/"))
}

function processResponse(resp) {
  var obj = JSON.parse(resp)
  if (obj.Answer != null) {
    appendAnswer(obj.Answer, obj.CountryCode)
  } else if (obj.Failure != null) {
    appendFailure(obj.Failure)
  } else {
    appendQuestion(obj)
  }
}

function appendAnswer(ans, code) {
  var e = document.createElement('div')
  e.innerHTML = `<h1 class="title is-1 is-success"><img src="/static/flags/${code}.png" class="flag"> <b>${ans}</b></h1>`
  document.getElementById("result").appendChild(e)
  unlockButton()
}

function appendFailure(msg) {
  var e = document.createElement('div')
  e.className = "notification is-danger"
  e.innerHTML = `<h1 class="title is-2 is-danger">we've failed to guess: <b>${msg}</b></h1>`
  document.getElementById("result").appendChild(e)
  unlockButton()
}

function unlockButton() {
  document.getElementById("reloadBtn").className = "button"
}

function startOver() {
  document.getElementById("startBtn").className = "button is-success"
  document.getElementById("questions").innerHTML = ""
  document.getElementById("result").innerHTML = ""
  document.getElementById("reloadBtn").className = "no-display"
}
