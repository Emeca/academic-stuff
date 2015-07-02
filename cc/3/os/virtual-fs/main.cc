#include "fat.hh"
#include "vfs.hh"

int
main()
{
	Vfs uhetfs("arquivo.bin", 1);;

	uhetfs.formatq();

	uhetfs.touch("teste", "uht");

	uhetfs.touch("teste2", "uht");

	uhetfs.touch("teste2", "uht");
	uhetfs.touch("teste2", "uht");

	uhetfs.ls();

	cout << endl << "-------------" << endl;

	uhetfs.close(uhetfs.getNomeVfs());

	uhetfs.connect(uhetfs.getNomeVfs());
	uhetfs.ls();

	return 0;
}
