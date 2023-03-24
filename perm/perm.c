#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    FALSE=0,
    TRUE=1
};

void swap(int ind1, int ind2, int n, char **s) {
    char *tmp=s[ind1];    
    s[ind1] = s[ind2];
    s[ind2] = tmp;
}

void sort(int n, char **s) {
    int min;
    // For each pointer
    for (int i=0; i<n-1; i++) {
        min=i;
        // Compare with later pointers
        for (int j=i+1; j<n; j++) {
            // Update min if j is lexicographically lower
            if (strcmp(s[j], s[min])<0) {
                min=j;
            }
        }
        // Swap current for sequence min
        if (min != i) {
            swap(i, min, n, &s[0]);
        }
    }
}

void sort_rev(int n, char **s) {
    int max;
    // For each pointer
    for (int i=0; i<n-1; i++) {
        max=i;
        // Compare with later pointers
        for (int j=i+1; j<n; j++) {
            // Update max if j is lexicographically higher
            if (strcmp(s[j], s[max])>0) {
                max=j;
            }
        }
        // Swap current for sequence min
        if (max != i) {
            swap(i, max, n, &s[0]);
        }
    }
}

int is_sorted(int n, char **s) {
    for (int i=0; i<n-1; i++) {
        if (strcmp(s[i],s[i+1])>0) {
            return FALSE;
        }
    }
    return TRUE;
}

int is_sorted_rev(int n, char **s) {
    for (int i=0; i<n-1; i++) {
        if (strcmp(s[i],s[i+1])<0) {
            return FALSE;
        }
    }
    return TRUE;
}

int get_next_largest(int n, char **s) {
    int max=1;
    int next_largest;
    for (int i=2; i<n; i++) {
        if(strcmp(s[i],s[max])>0) {
            max=i;
        }
    }
    next_largest=max;
    for (int i=1; i<n; i++) {
        if(strcmp(s[i],s[0])>0 & strcmp(s[i],s[next_largest])<0) {
            next_largest=i;
        }
    }
    return next_largest;
}

int next_permutation(int n, char **s)
{
	/**
	* Complete this method
	* Return 0 when there is no next permutation and 1 otherwise
	* Modify array s to its next permutation
	*/
    
    /* 
    * If the next lowest order (NLO) sequence is in reverse lexicographical order
    * or only one element remains, then swap the current element with the next 
    * highest in the NLO sequence and reorder the resulting NLO sequence in
    * lexiographical order. Else recurse and repeat process for the NLO sequence.
    */
    int next_largest;
    int n_next=n-1;
    char **s_next=&s[1];
    if (is_sorted_rev(n, s)) {
        return 0;
    } else if (n_next == 1) {
        swap(0, 1, n, s);
    } else if (is_sorted_rev(n_next, s_next)) {
        next_largest=get_next_largest(n, s);
        swap(0, next_largest, n, s);
        sort(n_next, s_next);
    } else {
        next_permutation(n_next, s_next);
    }
    return 1;
}

int main()
{
	char **s;
	int n;
	scanf("%d", &n);
	s = calloc(n, sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		s[i] = calloc(11, sizeof(char));
		scanf("%s", s[i]);
	}
	do
	{
		for (int i = 0; i < n; i++)
			printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
	} while (next_permutation(n, s));
	for (int i = 0; i < n; i++)
		free(s[i]);
	free(s);
	return 0;
}
