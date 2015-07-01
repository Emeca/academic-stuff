#include "bmp.hh"
#include "conf.hh"
#include "parser.hh"
#include "render.hh"

#define RESOLUCAO 32

int
main(int argc, char *argv[])
{
	Parser *parser = NULL;
	Conf *conf = NULL;
	Bmp *bmp = NULL;
	Render *render = NULL;
	if (argc > 2) {
//  if (argc > 0) {
		conf = new Conf();
		parser = new Parser(conf, argv[1]);
		delete(parser);
//      parser = new Parser(conf,"uhetrender.conf"); delete(parser);
		bmp =
			new Bmp((int)rint(conf->camera->interior[LARGURA]),
					(int)rint(conf->camera->interior[ALTURA]), RESOLUCAO);
		render = new Render(conf, bmp);
		conf->print();
		bmp->WriteToFile(argv[2]);
//      bmp->WriteToFile("uhet.bmp");
	} else {
		cout << "oops: digita certo rapaiz!!!" << endl;
		cout << "sintaxe: " << argv[0] <<
			" <arquivo_de_configuracao> <arquivo_de_saida>" << endl;
	}
	delete(render);
	delete(bmp);
	delete(conf);
	cout << "maravilha alberto!" << endl;
	return 0;
}
