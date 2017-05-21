#include <stdio.h>

struct Character {
  int initiative;
  char name[20];
};

void swap(struct Character arr[], int i, int j) {
  if (i == j) return;

  struct Character temp;
  temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

void sortCharacters(struct Character arr[], int left, int right) {

  // if the array has fewer than two elements do nothing.
  // we use '>=' here in case for some CRAZY reason this function is called
  // with a left that is greater than the right
  // Yeah......like that will happen, right?
  // btw, this is called defensive programming. Dummy
  if (left >= right) return;

  // Set the partition element, the middle element here, on the leftmost array position
  swap(arr, left, (left + right) / 2);

  /*
    go through the array and throw items to the left,
    if they're smaller than the partitionElem,
    or the left if they're smaller than the partitionElem
  */
  int newPartitionPosition = left;
  for(int i = left + 1; i <= right; i++) {
    if (arr[i].initiative < arr[left].initiative)
      swap(arr, ++newPartitionPosition, i);
  }

  swap(arr, left, newPartitionPosition);

  sortCharacters(arr, left, newPartitionPosition - 1);
  sortCharacters(arr, newPartitionPosition + 1, right);
}

int main () {
  int numPlayers;
  printf("How many players are there?: ");
  scanf("%d", &numPlayers);

  int numEnemies;
  printf("How many enemies are there?: ");
  scanf("%d", &numEnemies);

  int sum;
  sum = numEnemies + numPlayers;
  printf("There are %d players and %d enemies for a total of %d characters\n", numPlayers, numEnemies, sum);

  struct Character characters[sum];

  for (int i = 0; i < sum ; i++) {
    printf("Character's Name: ");
    scanf("%s", characters[i].name);

    printf("Character's Initiative: ");
    scanf("%d", &characters[i].initiative);
  }

  // sort the characters
  sortCharacters(characters, 0, sum - 1);

  // clear the screen
  printf("\033[H\033[J");

  int c;
  int pointer = 0;

  while ((c = getchar()) != EOF) {
    // move to the first row and column, clear the line from cursor to end of line
    printf("\033[H\033[K");

    for (int i = 0; i < sum; i++) {
      if (pointer == sum) {
        pointer = 0;
      }

      // set cursor to dim
      printf("\033[0m");
      // print marker if it's this player's turn
      if (pointer == i) printf("\033[4m> ");
      printf("%d : %s\n\033[K", characters[i].initiative, characters[i].name);

    }

    //increment pointer
    pointer++;

  }
}
