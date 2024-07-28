const amqp = require("amqplib/callback_api");

const RABBITMQ_URL = "amqp://rabbitmq";
const RETRY_INTERVAL = 20000;

function connectToRabbitMQ() {
  amqp.connect(RABBITMQ_URL, (error0, connection) => {
    if (error0) {
      console.error(
        "Failed to connect to RabbitMQ, retrying in 5 seconds...",
        error0
      );
      return setTimeout(connectToRabbitMQ, RETRY_INTERVAL);
    }

    connection.createChannel((error1, channel) => {
      if (error1) {
        console.error("Failed to create a channel", error1);
        return;
      }

      const queue = "fila";

      channel.assertQueue(queue, {
        durable: true,
      });

      console.log(`[*] Waiting for messages in ${queue}. To exit press CTRL+C`);

      channel.consume(
        queue,
        (message) => {
          console.log(`[x] Received ${message.content.toString()}`);
        },
        {
          noAck: true,
        }
      );
    });
  });
}

connectToRabbitMQ();
