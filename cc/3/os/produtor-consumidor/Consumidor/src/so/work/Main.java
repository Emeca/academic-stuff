package so.work;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Main {

	public static void main(String[] args) {

		Socket cliente = null;
		ServerSocket server = null;

		DataOutputStream saida = null;
		DataInputStream entrada = null;

		try {
			/* escutando por conexoes */
			server = new ServerSocket(6666);

			/* estabelece a conexao */
			cliente = server.accept();

			saida = new DataOutputStream(cliente.getOutputStream());
			entrada = new DataInputStream(cliente.getInputStream());

			for (int i = 0; i < 100; i++)
				saida.writeInt(1);

			while (true) {

				/* chegou item */
				if (entrada.readInt() == 2) {
					/* consumo item, diminui o buffer e requisita outro */
					saida.writeInt(1);
				}
			}

		} catch (IOException ioe) {
			System.err.println(ioe);
		}

		finally {

			try {
				if (server != null)
					server.close();
				if (cliente != null)
					cliente.close();
				if (saida != null)
					saida.close();
				if (entrada != null)
					entrada.close();

			} catch (IOException e) {
				e.printStackTrace();
			}
		}

	}
}
