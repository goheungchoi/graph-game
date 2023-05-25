/**
 * Websocket API
 */
class WSApi {
  constructor(host = null) {
    const hostname =
      host != null
        ? host
        : location.hostname + (location.port ? ":" + location.port : "");
    this.socket = new WebSocket("ws://" + hostname, "web_server");
    this.callbacks = {};
    this.requestId = 0;
    this.id = null;

    this.onmessage = null;

    this.socket.onmessage = (msg) => {
      let data = JSON.parse(msg.data);

      if (typeof data == "number") {
        this.id = +msg.data;
        this.connected = true;
        console.log(this.id);
        return;
      }

      if ("id" in data && data.id in this.callbacks) {
        this.callbacks[data.id](data);
      }

      if (this.onmessage) {
        this.onmessage(msg, data);
      } else {
        console.log('onmessage() undefined\n');
      }
    };

    this.connect = new Promise((resolve, reject) => {
      this.socket.onopen = () => {
        resolve(this.socket);
      };

      this.socket.onerror = (err) => {
        console.log(err);
        reject(err);
      };

      this.socket.onclose = (event) => {
        console.log(event);
      };
    });

    this.connected = false;

    this.connect.then(() => {
      this.connected = true;
    });
  }

  sendPostCommand(cmd, data, calcVal) {
    console.log(this.id);
    return this.sendCommand(cmd, data, calcVal, true);
  }

  sendCommand(cmd, data, calcVal, isPost = false) {
    if (this.connected) {
      data.cmd = cmd;
      data.id = this.requestId;

      if (isPost) {
        $.ajax({
          type: "POST",
          url: "/post/" + this.id,
          data: JSON.stringify(data),
          success: (res) => {
            console.log(res);
          },
          error: (res) => {
            console.log(res);
          },
          dataType: "json",
        });
      } else {
        this.socket.send(JSON.stringify(data));
      }

      let promise = new Promise((resolve, reject) => {
        this.callbacks[this.requestId] = (data) => {
          if (calcVal) {
            resolve(calcVal(data));
          } else {
            resolve(data);
          }
          delete this.callbacks[data.id];
        };
      });

      this.requestId++;
      return promise;
    } else {
      return new Promise((resolve, reject) => {
        this.connect.then(() => {
          this.connected = true;
          this.sendCommand(cmd, data, calcVal).then((data) => {
            resolve(data);
          });
        });
      });
    }
  }
}

var ws = new WSApi("localhost");

export default ws;