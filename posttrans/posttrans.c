/*
* Post Transit (Exercise)
* Source: HackerRank
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 6

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;

void print_all_packages(town t) {
    printf("%s:\n", t.name);
    // Offices in town
    for (int o=0; o<t.offices_count; o++) {
        printf("\t%d:\n", o);
        // Packages in office
        for (int p=0; p<t.offices[o].packages_count; p++) {
            printf("\t\t%s\n", t.offices[o].packages[p].id);
        }
    }
}

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {	
    int repeat=0;
    // Create post office pointers
    post_office *sop=&source->offices[source_office_index];
    post_office *top=&target->offices[target_office_index];
    // Deliver packages
    for (int p=0; p<sop->packages_count; p+=1-repeat) {
        repeat=0;
        if (sop->packages[p].weight <= top->max_weight &
            sop->packages[p].weight >= top->min_weight) {
            // Realloc target
            top->packages=realloc(top->packages, sizeof(package)*(top->packages_count+1));
            top->packages[top->packages_count].id=(char*)malloc(MAX_STRING_LENGTH*sizeof(char*));
            // Transfer package to target
            top->packages[top->packages_count]=sop->packages[p];
            // Update target package count
            top->packages_count++;
            // Remove package from source
            for (int n=p; n<sop->packages_count-1; n++) {
                sop->packages[n]=sop->packages[n+1];
            }
            // Ralloc source
            sop->packages=realloc(sop->packages,sizeof(package)*(sop->packages_count-1));
            // Update source count and rmcount
            repeat=1;
            sop->packages_count--;
        }
    }
}

town town_with_most_packages(town* towns, int towns_count) {
    int town_total;
    int max=0;
    town maxtown=towns[0];
    // For each town
    for (int t=0; t<towns_count; t++) {
        town_total=0;
        // Sum the packages from the offices
        for (int o=0; o<towns[t].offices_count; o++) {
            town_total+=towns[t].offices[o].packages_count;
        }
        // Update max and town if current is greater
        if (town_total>max) {
            max=town_total;
            maxtown=towns[t];
        }
    }
    return maxtown;
}

town* find_town(town* towns, int towns_count, char* name) {
    town *result;
    for (int t=0; t<towns_count; t++) {
        // Check exact match
        if (strcmp(towns[t].name, name)==0) {
            // Set result to address of town
            result=&towns[t];
            break;
        }
    }
    return result;
}

int main()
{
	int towns_count;
	scanf("%d", &towns_count);
	town* towns = malloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
		scanf("%s", towns[i].name);
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
				scanf("%s", towns[i].offices[j].packages[k].id);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	int queries;
	scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--) {
		int type;
		scanf("%d", &type);
		switch (type) {
		case 1:
			scanf("%s", town_name);
			town* t = find_town(towns, towns_count, town_name);
			print_all_packages(*t);
			break;
		case 2:
			scanf("%s", town_name);
			town* source = find_town(towns, towns_count, town_name);
			int source_index;
			scanf("%d", &source_index);
			scanf("%s", town_name);
			town* target = find_town(towns, towns_count, town_name);
			int target_index;
			scanf("%d", &target_index);
			send_all_acceptable_packages(source, source_index, target, target_index);
			break;
		case 3:
			printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
			break;
		}
	}
	return 0;
}
