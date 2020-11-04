#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <random>

using namespace std;



struct buckets
{
  float dane;
  buckets *next_elem;
};

struct ind_buck
{
  buckets *head_elem;
};

const int n = 10;
const float A = 0;
const float B = 100;

int M[n];

void sort_Bubble(float *T, int dl)
{
  float tym;
  for(int i=0; i<dl-1; i++)
    for(int j=0; j<dl-1-i; j++)
      {
        if(T[j] > T[j+1])
          {
            tym = T[j];
            T[j] = T[j+1];
            T[j+1] = tym;
          }
      }
}
void sort_Bucket(float *T, int dl,ind_buck *table_buck)
{
  int temp;
  buckets *current_elem;
  for(int i=0; i<dl; i++)
    {
      temp = (T[i] / n);
      if(T[i] == 100)
        temp = n-1;

      current_elem = new buckets;
      current_elem->next_elem = table_buck[temp].head_elem;
      current_elem->dane = T[i];
      table_buck[temp].head_elem = current_elem;
    }

  //////////// sort
  buckets *current, *previous, *before_current, *tempp;
  for(int i=0; i<n; i++)
    {
      current = table_buck[i].head_elem;
      while(current != NULL)
        {
          float curr_count = current->dane;

          tempp = table_buck[i].head_elem;
          if(tempp->next_elem != NULL && current != tempp)   // jezeli lista ma tylko jeden element i aktualny element nie jest sprawdzanym elementem
            {
              bool is_changed = false;
              while(is_changed == false && current != tempp) // petla nie przekracza aktualnej zmiennej
                {
                  if(curr_count < tempp->dane)
                    {
                      if(tempp == table_buck[i].head_elem)
                        {
                          before_current->next_elem = current->next_elem;
                          current->next_elem = table_buck[i].head_elem;
                          table_buck[i].head_elem = current;
                          current = before_current;
                        }
                      else if(curr_count != tempp->dane)
                        {
                          before_current->next_elem = current->next_elem;
                          current->next_elem = tempp;
                          previous->next_elem = current;
                          current = before_current;
                        }
                      is_changed = true;
                    }
                  previous = tempp;
                  tempp = tempp->next_elem;
                }
            }
          before_current = current;
          current=current->next_elem;
        }
    }

  int point_Tab = 0;

  for(int i=0; i<n; i++)
    {
      if(table_buck[i].head_elem != NULL)
        {
          tempp = table_buck[i].head_elem;
          while(tempp != NULL)
            {
              T[point_Tab] = tempp->dane;
              tempp = tempp->next_elem;
              point_Tab ++;
            }
        }
    }

  for(int i=0; i<n; i++)
    {
      if(table_buck[i].head_elem != NULL)
        {
          tempp = table_buck[i].head_elem;
          while(tempp != NULL)
            {
              current = tempp;
              tempp = tempp->next_elem;
              delete current;
            }
        }
    }
}
int main()
{
  float *T1, *T2;
  ind_buck table_buck[n];
  int los, choice, typ;
  char numb_after_sort, numb_before_sort;
  clock_t start, stop;
  float time;
  default_random_engine generator;
  normal_distribution<double> distribution(50.0,10.0);

  srand(time(0));

  cout << "_____________________________"<<endl;
  cout << setw(15) << "Welcome" << endl;

  do
    {
      cout << "-----------------------------"<<endl;
      cout << setw(20) << "Main MENU" << endl;
      cout << "-----------------------------"<<endl;
      cout << "1.Compare the algorithms" << endl;
      cout << "2.Exit" << endl;
      cout << "-----------------------------"<<endl;
      cout << "Select: ";
      cin >> choice;

      if(choice == 1)
        {
          cout << "How many numbers do you want to draw?" << endl;
          cin >> los;
          cout << "What type of numbers do you want to test? " << endl;
          cout << "1.Random numbers." << endl;
          cout << "2.Sorted numbers."  << endl;
          cout << "3.Partially ordered numbers." << endl;
          cout << "4.Numbers in normal distribution." << endl;

          cin >> typ;
          while(typ != 1 && typ != 2 && typ != 3 && typ !=4)
            {
              cout << "Wrong choice, try again: ";
              cin >> typ ;
            }

          cout << "Do you want to print the drawn numbers? (Y/N) " ;
          cin >> numb_before_sort;
          while(numb_before_sort != 'y' && numb_before_sort != 'Y' && numb_before_sort != 'n' && numb_before_sort != 'N')
            {
              cout << "Wrong choice, try again: ";
              cin >> numb_before_sort ;
            }


          T1 = new float[los];
          T2 = new float[los];

          int inserted = 0;
          int j = 0;
          int howMany = los/B;

          switch(typ)
            {
            case 1:
              for(int i=0; i<los; i++)
                T1[i] = B*rand()/float(RAND_MAX);
              break;
            case 2:
              for(int i=0; i<los; i++)
                {
                  if(j == howMany)
                    {
                      inserted++;
                      j=0;
                    }
                  if(howMany > 0)
                    j++;
                  T1[i] = inserted;
                }
              break;
            case 3:
            {
              for(int i=0; i<los; i++)
                {
                  if(j == howMany)
                    {
                      inserted++;
                      j=0;
                    }
                  if(howMany > 0)
                    j++;
                  T1[i] = inserted;
                }
              int procent = (los*5)/100;
              for(int i=0; i<procent; i++)
                {
                  int rand_p = rand()%los;
                  int rand_c = rand()%los;
                  int temp = T1[rand_p];
                  T1[rand_p] = T1[rand_c];
                  T1[rand_c] = temp;
                }
            }
            break;
            case 4:
            {
              float temp;
              for(int i=0; i<los; i++)
                {
                  temp = distribution(generator);
                  if(temp < 0)
                    temp = 0;
                  else if(temp > 100)
                    temp = 100;
                  T1[i]=temp;
                }
            }
            break;
            };


          cout << endl;

          for(int i=0; i<los; i++)
            T2[i] = T1[i];

          int break_line = 0;
          if(numb_before_sort == 'T' || numb_before_sort == 't')
            {
              cout << "Drawn numbers :" << endl;
              for(int i=0; i<los; i++)
                {
                  if(break_line == 20)
                    {
                      cout << endl;
                      break_line = 0;
                    }

                  cout <<  setprecision(3) << T1[i] << '\t';
                  break_line ++;
                }
            }
          else
            {
              cout << "The drawn numbers will not be printed" ;
            }

          cout << endl;



          cout << endl << "A bubble sort is in progress:   " ;
          start = clock();
          sort_Bubble(T1,los);
          stop = clock();
          time = (float)(stop - start) / CLOCKS_PER_SEC;

          cout << endl <<  "Bubble sort took over: " << time << " sek." << endl << endl;

          cout << "Display sorted numbers \"BubbleSort\"? (Y/N) ";
          cin >> numb_after_sort ;
          cout << endl;
          while(numb_after_sort != 'y' && numb_after_sort != 'Y' && numb_after_sort != 'n' && numb_after_sort != 'N')
            {
              cout << "Wrong choice, try again: ";
              cin >> numb_after_sort ;
            }
          break_line = 0;
          if(numb_after_sort == 'Y' || numb_after_sort == 'y')
            {
              cout << "Sorted numbers :" << endl;
              for(int i=0; i<los; i++)
                {
                  if(break_line == 20)
                    {
                      cout << endl;
                      break_line = 0;
                    }
                  cout <<  setprecision(3) << T1[i] << '\t';
                  break_line ++;
                }
            }
          else
            {
              cout << "The sorted numbers will not be printed" ;
            }
          cout << endl;

          for(int i=0; i<n; i++)
            {
              table_buck[i].head_elem = NULL;
            }

          cout << endl << "The bucket sort is in progress   " ;
          start = clock();
          sort_Bucket(T2,los, table_buck);
          stop = clock();
          time = (float)(stop - start) / CLOCKS_PER_SEC;

          cout << endl <<  "Bucket sort took over: " << time << " sek." << endl << endl;

          cout << "Display sorted numbers \"BucketSort\"? (Y/N) ";
          cin >> numb_after_sort ;
          cout << endl;
          while(numb_after_sort != 'y' && numb_after_sort != 'Y' && numb_after_sort != 'n' && numb_after_sort != 'N')
            {
              cout << "Wrong choice, try again: ";
              cin >> numb_after_sort ;
            }
          break_line = 0;
          if(numb_after_sort == 'Y' || numb_after_sort == 'y')
            {
              cout << "Sorted numbers :" << endl;
              for(int i=0; i<los; i++)
                {
                  if(break_line == 20)
                    {
                      cout << endl;
                      break_line = 0;
                    }

                  cout <<  setprecision(3) << T1[i] << '\t';
                  break_line ++;
                }
            }
          else
            {
              cout << "The sorted numbers will not be printed" ;
            }
          cout << endl << endl;
          delete[] T1;
          delete[] T2;
        }
      else if(choice != 2)
        cout << endl << "There's no such option." << endl << endl;
    }
  while(choice != 2);


  return 0;
}
