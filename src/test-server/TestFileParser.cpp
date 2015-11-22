//
// Created by Helen Hwang on 11/18/15.
//
#include <sstream>
#include "TestFileParser.h"

using namespace rapidxml;
/**
 * This initializes the parser
 */
void TestFileParser::load() {
   // loading document
   std::ifstream file(testFile);
   if (!file) std::cerr << "Could not open the file '"<<testFile<<"'!" << std::endl;
   else {
      std::stringstream buffer;
      buffer << file.rdbuf();
      file.close();
      std::string content(buffer.str());
      doc.parse<0>(&content[0]);

      // reads the document
      buildTestCase();
   }
}

/**
 * Reads the test case information
 */
void TestFileParser::buildTestCase()
{
   std::cout<<"\n------------------------------------------------------"<<std::endl;
   xml_node<> *node = doc.first_node("test");
   xml_node<> *inside = node->first_node("name");
   std::cout<<"Test name: "<<inside->value()<<std::endl;
   inside = node->first_node("description");
   std::cout<<"Test description: "<<inside->value()<<std::endl;
   std::cout<<"------------------------------------------------------"<<std::endl;
    /*<MyBeerJournal>
    <Brewery name="Founders Brewing Company" location="Grand Rapids, MI">
        <Beer name="Centennial" description="IPA" rating="A+" dateSampled="01/02/2011">
            "What an excellent IPA. This is the most delicious beer I have ever tasted!"
        </Beer>
    </Brewery>
    <Brewery name="Brewery Vivant" location="Grand Rapids, MI">
        <Beer name="Farmhouse Ale" description="Belgian Ale" rating="B" dateSampled="02/07/2015">
            This beer is not so good... but I am not that big of a fan of english style ales.
        </Beer>
    </Brewery>
    <Brewery name="Bells Brewery" location="Kalamazoo, MI">
        <Beer name="Two Hearted Ale" description="IPA" rating="A" dateSampled="03/15/2012">
            Another execllent brew. Two Hearted gives Founders Centennial a run for it's money.
        </Beer>
    </Brewery>
</MyBeerJournal>*/
   /*
   // Iterate over the brewerys
   for (xml_node<> * brewery_node = root_node->first_node("Brewery"); brewery_node; brewery_node = brewery_node->next_sibling())
   {
      printf("I have visited %s in %s. ",
             brewery_node->first_attribute("name")->value(),
             brewery_node->first_attribute("location")->value());
      // Interate over the beers
      for(xml_node<> * beer_node = brewery_node->first_node("Beer"); beer_node; beer_node = beer_node->next_sibling())
      {
         printf("On %s, I tried their %s which is a %s. ",
                beer_node->first_attribute("dateSampled")->value(),
                beer_node->first_attribute("name")->value(),
                beer_node->first_attribute("description")->value());
         printf("I gave it the following review: %s", beer_node->value());
      }
      cout << endl;
   }*/
}

