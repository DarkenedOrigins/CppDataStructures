/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string& infile)
    : filename(infile)
{
    /* nothing */
}

template <template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold) const
{
    TextFile infile(filename);
    vector<pair<string, int>> ret;
    /**
     * @todo Implement this function.
     * @see char_counter.cpp if you're having trouble.
     */
	Dict<string, int> Dictionary(251); //251 is a prime number and is pretty large since we are looking at book
	while(infile.good() ){
		string word = infile.getNextWord(); //get next word
		Dictionary[word] += 1;//the [] oper adds word if it doesnt exist and also returns the default val by ref 
	}
	for(auto it = Dictionary.begin(); it != Dictionary.end(); it++){
		if(it->second >= threshold){ //if the val(amount of time seen is >= thres add it to the vec
			ret.push_back(*it);
		}
	}
	return ret;
}
