var samples = [
  "p,x,s,n,t,p,f,c,n,k,e,e,s,s,w,w,p,w,o,p,k,s,u",
  "e,x,s,y,t,a,f,c,b,k,e,c,s,s,w,w,p,w,o,p,n,n,g",
  "e,b,s,w,t,l,f,c,b,n,e,c,s,s,w,w,p,w,o,p,n,n,m",
  "p,x,y,w,t,p,f,c,n,n,e,e,s,s,w,w,p,w,o,p,k,s,u",
  "e,x,s,g,f,n,f,w,b,k,t,e,s,s,w,w,p,w,o,e,n,a,g",
  "e,x,y,y,t,a,f,c,b,n,e,c,s,s,w,w,p,w,o,p,k,n,g",
  "e,b,s,w,t,a,f,c,b,g,e,c,s,s,w,w,p,w,o,p,k,n,m",
  "e,b,y,w,t,l,f,c,b,n,e,c,s,s,w,w,p,w,o,p,n,s,m"
];

function httpGet(theUrl) {
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", theUrl, false);
    xmlHttp.send(null);
    return xmlHttp.responseText;
}

function train() {
  resp = httpGet("/train/")
  // console.log("train response: ", resp)
  document.getElementById("trainResponse").innerHTML = resp
  document.getElementById("validateSection").className = ""
}

function validate() {
  resp = httpGet("/validate/")
  console.log("validate response: ", resp)
  document.getElementById("validateResponse").innerHTML = resp
  document.getElementById("recognizeSection").className = ""
  showSamples()
}

function showSamples() {
  var e = document.getElementById("mushrooms-to-recognize")
  for (var i = 0; i < samples.length; i++) {
    e.innerHTML += `
      <div class="mushroom-sample row" id="sample-${i}" onclick="recognize(${i})">${samples[i].substring(2)}</div>
      <div class="row" id="sample-response-${i}"></div>
      <br>
    `
  }
}

function recognize(i) {
  // console.log(i)
  resp = httpGet("/recognize/" + i + "/")
  // document.getElementById("sample-response-"+i).innerHTML = resp
  console.log(resp)
  var cl = resp.substring(resp.length-1)
  if (cl === samples[i].substring(0,1)) {
    document.getElementById("sample-"+i).style = "border: 4px solid green"
  } else {
    document.getElementById("sample-"+i).style = "border: 4px solid red"
  }
}
