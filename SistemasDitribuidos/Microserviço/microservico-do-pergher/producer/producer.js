const amqp = require("amqplib/callback_api");

const RABBITMQ_URL = "amqp://rabbitmq:5672";
const RETRY_INTERVAL = 20000; // 20 seconds

function connectToRabbitMQ() {
  console.log("Connecting to RabbitMQ...");

  amqp.connect(RABBITMQ_URL, (error0, connection) => {
    if (error0) {
      console.error(
        "Failed to connect to RabbitMQ, retrying in 20 seconds...",
        error0.message
      );
      return setTimeout(connectToRabbitMQ, RETRY_INTERVAL);
    }

    connection.createChannel((error1, channel) => {
      if (error1) {
        console.error("Failed to create a channel", error1.message);
        return;
      }

      const queue = "fila";

      channel.assertQueue(queue, {
        durable: true,
      });

      setInterval(() => {
        const message = Math.floor(Math.random() * 100 + 1).toString();
        channel.sendToQueue(queue, Buffer.from(message));
        console.log(`[x] Sent ${message}`);
      }, 150);
    });
  });
}

connectToRabbitMQ();
