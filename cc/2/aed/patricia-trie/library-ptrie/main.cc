#include "tree.hh"

int
main(void)
{
	Tree *A = new Tree();

//  A->add("a");
//  A->add("b");
//  A->add("c");
//  A->add("d");
//  A->add("e");
//  A->add("f");
//  A->add("g");
//  A->add("h");
//  A->add("i");
//  A->add("j");
//  A->add("k");
//  A->add("l");
//  A->add("m");
//  A->add("n");
//  A->add("o");
//  A->add("p");
//  A->add("q");

	A->add("unha");
	A->add("abacate");
//  A->add("coco");
//  A->add("inhaca");
	A->add("uheti");
	A->add("uhetima");
	A->add("uhetimo");
//  A->add("coco");
	A->add("urubu");

	A->printArvore();
	cout << "total de palavras: " << A->getTamanho() << endl;
	cout << A->consulta("uhet") << endl;

	stack < No * >*pilha = A->empilha("uhet");
	cout << "montagem da pilha: " << A->pilha_to_string(pilha) << endl;;
	cout << pilha->top()->getRadical();

//  vector<string>* vet = A->sugestao("uhet",5);

//  for (vector<string>::iterator it = vet->begin(); it != vet->end(); it++)
//      cout << *it << endl;

	A->deltree();
	return 0;
}
