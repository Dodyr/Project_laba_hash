#include <iostream>
#include <Windows.h>
#include <vector>

#include "Header1.h"

//функция предполагает, что список публикаций отсортирован по количеству страниц по возрастанию
void destroy_books(Hash_table& table, Sorter& sorter)
{
	TIterator i = sorter.begin();
    int min_pages = (*i)->GetNPages();
    while ((*i)->GetNPages() == min_pages && i != sorter.end())
    {
        Book* book = dynamic_cast<Book*>(*i);
        if (book && book->getBinding() == "softcover")
        {
            table.Delete(book->getName());
            i = sorter.erase(i); 
            delete book;
        }
        else
            i++;
    }
}

void sort_(Sorter& sorter)
{
	auto cmp = [](Publication* a, Publication* b)->bool {return a->GetNPages() < b->GetNPages(); };
	sorter.sort(cmp);
}

int main()
{
    setlocale(LC_ALL, "Rus");
    std::ifstream fin("lbr.txt");
    if (fin.is_open())
    {
        Hash_table table;
        Sorter sorter = Hash_full(fin, table);
		sort_(sorter);
        destroy_books(table, sorter);
        print_(sorter);
    }
    fin.close();
    return 0;
}