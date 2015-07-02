package so.work;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

public class Main {

	public static void main(String[] args) {

		String host;
		Socket cliente = null;

		DataOutputStream saida = null;
		DataInputStream entrada = null;

		if (args.length == 0)
			host = "127.0.0.1";
		else
			host = args[0].trim();

		try {
			cliente = new Socket(host, 6666);

			saida = new DataOutputStream(cliente.getOutputStream());
			entrada = new DataInputStream(cliente.getInputStream());

			while (true) {

				/* chegou requisicao de producao */
				if (entrada.readInt() == 1) {
					/* produz e invia */
					saida.writeInt(2);
				}

			}

		} catch (IOException ioe) {
			System.err.println(ioe);
		}

		finally {

			try {
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
