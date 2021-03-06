var helpers = require('./SerialHelpers');

var onEnd;

function init(onEndHandler,onErrorHandler){
  var handlers = {
    handshakeHandler: handleHandshake,
    handshakeEndHandler: handleHandshakeEnd
  };
  onEnd = onEndHandler;
  helpers.init(handlers,() =>{
    helpers.sendResetMessage();
  }, onErrorHandler);
}

function handleHandshake(){
  helpers.answerToHandshake();
  return;
}

function handleHandshakeEnd(){
    console.log("Handshake ended!");
    if(onEnd)
      onEnd();
}


module.exports = {
  init
}
