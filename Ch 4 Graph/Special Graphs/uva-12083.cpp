//Finding Maximum Independent Set in Bipartite Graph by finding MCBM
//UVa - UVa 12083 - Guardian of Decency - Find MIS - MIS = V - MCBM
//Find Max Cardinality Bipartite Matching using Augmenting Paths Algo

/*Note: MCBM can also be solved by Max Flow on Bipartite Graph by 
  assigning SuperSource to left set and SuperSink to right set vertices*/ 

#include <iostream>
#include <vector>
#include <string>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;

struct student
{
    int ht;                      //Height                  
    string mu, sp;              //Music, Sport
};

vvi AdjList;
vi match;                      //Assigning a boy as match to a girl
vb visited;                   //Prevent revisiting vertices while matching

bool Augment( int u ) 
{
    if( visited[u] )        //No augmenting path found, return 0
        return 0;

    visited[u] = true;      //u is now visited in this iteration

    //For all possible matches u - v 
    for( auto &v : AdjList[u] )

        //If v not matched already, match u - v
        //Else try to find a separate match for match[v]( augmenting path )
        if( match[v] == -1 || Augment( match[v] ) )
        {
            match[v] = u;                            //Match v to u
            return 1;                               //1 more match
        } 
    return 0;           //No matches found for u, returning 0    
}

int main()
{
    int T, N;                         //Problem parameters
    int ht;                          //Height                        
    char sx;                        //Sex
    string mu, sp;                 //Music, Sport
    scanf( "%d", &T );
    while( T-- )
    {
        //Setting up Bipartite Graph from Input
        vector<student> boys, girls;
        scanf( "%d", &N );
        for( int i{ 0 }; i < N; ++i )               
        {
            cin >> ht >> sx >> mu >> sp;
            if( sx == 'M')
                boys.push_back( { ht, mu, sp } );      //Boys one side
            else
                girls.push_back( { ht, mu, sp } );   //Girls other side
        }

        //Setting up Adjacency List by pairing vertices( couples )
        int noBoys = boys.size();
        int noGirls = girls.size();
        AdjList.assign( N, vi() );


        //0 to noBoys - 1 are boys, noBoys to noGirls - 1 are girls
        for( int b{ 0 }; b < noBoys; ++b )
            for( int g{ 0 }; g < noGirls; ++g )
            {
                if( ( abs( boys[b].ht - girls[g].ht ) <= 40 )
                && ( boys[b].mu == girls[g].mu )
                && ( boys[b].sp != girls[g].sp ) )    //Possible couple

                    AdjList[b].push_back( g + noBoys ); //Directed edge
            }

        //Find out Maximum Cardinality Bipartite Matching
        int MCBM = 0;
        match.assign( N, -1 );

        //Start with an unmatched left vertex( boy ) in each iteration
        for( int u{ 0 }; u < noBoys; ++u )
        {
            //Reset so that its possible to change matchings if needed
            visited.assign( noBoys, false );
            
            //Adds 1 if a matching can be added, 0 otherwise
            MCBM += Augment( u );  
        }

        //We know Minimum Vertex Cover = No of vertices - MCBM
        printf( "%d\n", N - MCBM );

    }
}