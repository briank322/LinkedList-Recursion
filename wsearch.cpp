#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Location
{
  Location()
  {
    row = -1;
    col = -1;
  }
  Location(int r, int c)
  {
    row = r;
    col = c;
  }
  int row;
  int col;
};

// @param[in] instream - Input (file) stream for the input file.  Opened in main()
// @param[out] grid Blank vector of vectors.  Should be updated with the
//                  contents of the grid from the input file
// @return true if successful, false otherwise (see HW writeup for details
//         about possible error cases to be checked)
bool readGrid(istream& instream, vector<vector<char> >& grid )
{
  /** You complete **/
vector<char> cur_vec;
string line;
char cur_cha;

//used the similar structure as streams lecture notes pg11.
//implement the getline(file, line) and stringstream to store each characters.
while(getline(instream, line))
{
  stringstream ss(line);
  if(instream.fail())
  {
    cout<<"The line is empty"<<endl;
    break;
  }
  //if input file is valid,
  else if(!instream.fail())
  {
  //use push_back(add) to and store it to a vector
     while(ss>>cur_cha)
    {
       if(ss.fail())
      {
        cout<<"Error"<<endl;
        break;
      }
      //add new chars from the input txt line to the current vector.
      cur_vec.push_back(cur_cha);
    }
  }
  //store current line to a vector.
  grid.push_back(cur_vec);

  
  //check whether all rows has the same size 
  unsigned int i = 0;
  while ( i<grid.size())
  {
      if(grid[i].empty())
      {
        return false;
      } 
      if(grid[i].size() != grid[0].size())
      {
        return false;
      }
      i++;
   }
   // clear it before it gets to a new line
   cur_vec.clear();
   ss.clear();
   ss.str("");

 }
return true;
}

// prototype - will be implemented below
bool findWordHelper(
   const vector<vector<char> >& grid, 
   Location currLoc,
   Location delta,
   string word,
   unsigned int currWordIndex);

// Do not change
void printSolution
(const string& targetWord, const Location& start, string direction)
{
  cout << targetWord << " starts at (row,col) = (" << start.row << "," << start.col
       << ") and proceeds " << direction << "." << endl;
}

// Do not change
void printNoSolution(const string& targetWord)
{
  cout << targetWord << " does NOT occur." << endl;
}

// Complete - you should not need to change this.
void findWord(const vector<vector<char> >& grid, 
	      const string& targetWord)
{
  bool found = false;
  if(targetWord.size() < 2){
    cout << "Need a word of length 2 or more." << endl;
    return;
  }
  for(unsigned int r=0; r < grid.size(); r++){
    for(unsigned int c=0; c < grid[r].size(); c++){
      if(grid[r][c] == targetWord[0]){
	Location loc(r,c);
	if( findWordHelper(grid, Location(r-1,c), Location(-1, 0), targetWord, 1) ){
	  printSolution(targetWord, loc, "up");
	  found = true;
	}
	if( findWordHelper(grid, Location(r,c-1), Location(0,-1), targetWord, 1) ){
	  printSolution(targetWord, loc, "left");
	  found = true;
	}
	if( findWordHelper(grid, Location(r+1,c), Location(1, 0), targetWord, 1) ){
	  printSolution(targetWord, loc, "down");
	  found = true;
	}
	if( findWordHelper(grid, Location(r,c+1), Location(0,1), targetWord, 1) ){
	  printSolution(targetWord, loc, "right");
	  found = true;
	}
      }      
    }
  }
  if(!found){
    printNoSolution(targetWord);
  }
}

/**
 * @param[in] grid The 2D vector containing the entire search contents
 * @param[in] currLoc Current row and column location to try to match 
 *                    with the next letter
 * @param[in] delta   Indicates direction to move for the next search
 *                    by containing the *change* in row, col values
 *                    (i.e. 1,0 = down since adding 1 will move down 1 row)
 * @param[in] word The word for which you are searching
 * @param[in] currWordIndex The index to word indicating which letter must
 *                          be matched by this call
 */
bool findWordHelper(const vector<vector<char> >& grid, 
     Location currLoc,
     Location delta,
     string word,
     unsigned int currWordIndex)
{
  /*** You complete ***/
  //base case
  //check whether the word was fully inspected till the end
  if (currWordIndex == word.length())
   {
     return true;
   }

  //recursive cases
  // check whether it is a valid location (out of boundaries)
  else if(currLoc.row >= 0 && currLoc.col >=0)
  {
    if((currLoc.row < (int)grid.size())&&(currLoc.col < (int)grid[0].size()))
    {
      if((grid[currLoc.row][currLoc.col]==word[currWordIndex]))
      {
      	//if it is valid, update the current Location, 
      	//and move the current word indext to the next one.
        Location nextlocation(currLoc.row + delta.row, currLoc.col + delta.col);
        //Update current location to nextlocation by adding delta.
        //currLoc.row += delta.row
      	//currLoc.col += delta.col
        return findWordHelper(grid, nextlocation, delta, word, currWordIndex+1);
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }

  
}   
 
   


int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide a grid filename and targetWord" << endl;
    return 1;
  }
  ifstream ifile(argv[1]);
  string targetWord(argv[2]);
  if(ifile.fail()){
    cerr << "Unable to open input grid file" << endl;
    return 1;
  }

  vector<vector<char> > mygrid;
  if( ! readGrid(ifile, mygrid) ){
    cerr << "Error reading grid" << endl;
    ifile.close();
    return 1;
  }

  findWord(mygrid, targetWord);

  return 0;
  
}
