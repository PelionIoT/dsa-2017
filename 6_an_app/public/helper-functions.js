function getElement(endpoint) {
  return document.querySelector('li[data-endpoint="' + endpoint + '"]');
}

function updateStatusUi(endpoint, status) {
  var statusEl = getElement(endpoint).querySelector('.status');
  [].forEach.call(statusEl.children, function(el) {
    el.classList.remove('selected');
  });
  statusEl.querySelector('*[data-action="' + status + '"]').classList.add('selected');
}

function getDeviceName(endpoint, trim) {
  var el = document.querySelector('li[data-endpoint="' + endpoint + '"] .endpoint');
  var name = el ? el.textContent : endpoint;
  if (trim && name.length > 20) name = name.substr(0, 20) + '...';
  return name;
}

var notificationTo;
function showNotification(msg) {
  clearTimeout(notificationTo);

  var el = document.querySelector('#notification');
  el.textContent = msg;
  el.style.opacity = 1;
  el.style.visibility = 'visible';

  notificationTo = setTimeout(function() {
    el.style.opacity = 0;
    el.style.visibility = 'hidden';
  }, 6000);

  el.onclick = function() {
    clearTimeout(notificationTo);
    el.style.opacity = 0;
    el.style.visibility = 'hidden';
  };
}
