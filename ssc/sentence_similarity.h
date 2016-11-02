//=======================================================================
// Copyright 2013
// Authors: Xin Liu tonyxliu@hotmail.co.uk
//
// Distributed under GPL v2
//=======================================================================
#ifndef __SENTENCE_SIMILARITY_H__
#define __SENTENCE_SIMILARITY_H__

#include "wordnet_extended.h"

class SentenceSimilarity
{
private:
    SentenceSimilarity(const SentenceSimilarity&);
    SentenceSimilarity(SentenceSimilarity&&);
    SentenceSimilarity& operator=(const SentenceSimilarity&);
    SentenceSimilarity& operator=(SentenceSimilarity&&);

public:
    SentenceSimilarity() {}

    virtual ~SentenceSimilarity() {};

    virtual float compute_similarity(
        const std::string &,
        const std::string &,
        WordnetExtended::UndirectedGraph &) = 0;
};


///Li et al.(2006)
///http://ants.iis.sinica.edu.tw/3bkmj9ltewxtsrrvnoknfdxrm3zfwrr/55/Sentence%20Similarity%20Based%20on%20Semantic%20Nets%20and%20corpus%20statistics.pdf
class SentenceSimilarityLi2006
    : public SentenceSimilarity
{
private:
    ///Li et al.(2006) 3.1.3
    const float _S_ALPHA; //0.2f;
    const float _S_BETA; //0.45f;

    WordnetExtended& _wne;

    void build_sim_vector(
        WordnetExtended & wne,
        WordnetExtended::UndirectedGraph & graph,
        const std::vector<std::string> & s,
        const std::vector<std::string> & corpus,
        std::vector<float> & sim);

    float calc_cos_similarity(
        const std::vector<float> & sim1,
        const std::vector<float> & si2);

    float calc_word_sim(int length, int depth);

public:
    SentenceSimilarityLi2006(WordnetExtended& wne)
        : _wne(wne)
        , _S_ALPHA(0.2f)
        , _S_BETA(0.45f)
    {
    }

    virtual ~SentenceSimilarityLi2006() {}

    /// compute similarity between two sentences
    float compute_similarity(
        const std::string &,
        const std::string &,
        WordnetExtended::UndirectedGraph &);
};

#endif//__SENTENCE_SIMILARITY_H__