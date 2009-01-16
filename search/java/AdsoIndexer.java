import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.queryParser.QueryParser;
import org.apache.lucene.search.Hits;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import java.util.Date;
import java.io.*;

public class AdsoIndexer
{

  String indexDirectory = "/path/to/adso_index";

  // Fields in the Database
  String text = "";
  String segmented_utf8s   = "";
  String segmented_utf8c   = "";
  String segmented_pinyin  = "";
  String segmented_english = "";
  String link = "";
  String pubdate = "";


  // Fields for Search
  String searchField = "segmented_utf8s";
  String searchTerm  = "beef";
  



  private void indexFile(String filename) throws Exception {

    StandardAnalyzer analyzer = new StandardAnalyzer();
    IndexWriter writer;


    // Create new index if non-existent
    if (new File(indexDirectory).exists()) {
      writer = new IndexWriter(indexDirectory, analyzer, false);
    } else {
      writer = new IndexWriter(indexDirectory, analyzer, true);
    }


    String fileContents = "";

    try { 
	FileReader fr = new FileReader(filename); 
	BufferedReader in = new BufferedReader(fr);
	int i = 1;
	while (in.ready()) {

		// We Expect Well-Structured Data
		// fields are tab-separated in input file
		String linetoindex = in.readLine();
                String[] indexable = linetoindex.split("\t");
	
		i++;
  		text = "";
  		segmented_utf8s   = "";
  		segmented_utf8c   = "";
  		segmented_pinyin  = "";
  		segmented_english = "";
  		link = "";
  		pubdate = "";

		try {		

		text              = indexable[0];
		segmented_utf8s   = indexable[1];
		segmented_utf8c   = indexable[2];
		segmented_pinyin  = indexable[3];
		segmented_english = indexable[4];
		link              = indexable[5];
		pubdate           = indexable[6];

		} catch (Exception e) { System.out.println("Exception Caught here..."); }

		try {

			// Test to see if this has been added before... we use the link as a Unique ID for the document
			searchField = "link";
			searchTerm = link;
    			IndexSearcher is = new IndexSearcher(indexDirectory);
    			QueryParser parser = new QueryParser(searchField, analyzer);
    			Query query = parser.parse(searchTerm);
    			Hits hits = is.search(query);
	
			if (hits.length() > 0) { System.out.println("Already Indexed: " + title); }
			else {
				System.out.println("Indexing " + i + ": " + title);
        	     		Document document = createDocument();
  				writer.addDocument(document);
			}

		} catch (Exception e) { System.out.println("Exception caught.... searching..."); }

	}

    } catch (Exception e) { System.out.println(e); return; }

    writer.optimize();
    writer.close();    

    return;
  }






  private Document createDocument() {

    Document document = new Document();
    Field textField = new Field("text", text, Field.Store.COMPRESS, Field.Index.NO, Field.TermVector.NO);
    Field segmented_utf8sField = new Field("segmented_utf8s", segmented_utf8s, Field.Store.COMPRESS, Field.Index.TOKENIZED, Field.TermVector.YES);
    Field segmented_utf8cField = new Field("segmented_utf8c", segmented_utf8c, Field.Store.COMPRESS, Field.Index.TOKENIZED, Field.TermVector.YES);
    Field segmented_englishField = new Field("segmented_english", segmented_english, Field.Store.COMPRESS, Field.Index.TOKENIZED, Field.TermVector.YES);
    Field segmented_pinyinField = new Field("segmented_pinyin", segmented_pinyin, Field.Store.COMPRESS, Field.Index.TOKENIZED, Field.TermVector.YES);
    Field linkField = new Field("link", link, Field.Store.YES, Field.Index.NO, Field.TermVector.NO);
    Field pubdateField = new Field("pubdate", pubdate, Field.Store.COMPRESS, Field.Index.UN_TOKENIZED, Field.TermVector.NO);

    document.add(textField);
    document.add(segmented_utf8sField);
    document.add(segmented_utf8cField);
    document.add(segmented_englishField);
    document.add(segmented_pinyinField);
    document.add(linkField);
    document.add(pubdateField);

    return document;

  }







  private void searchIndex() {

	try {

    System.out.println("Searching for: " + searchTerm + " in " + searchField);

    IndexSearcher is = new IndexSearcher(indexDirectory);
    StandardAnalyzer analyzer = new StandardAnalyzer();
    QueryParser parser = new QueryParser(searchField, analyzer);
    Query query = parser.parse(searchTerm);
    Hits hits = is.search(query);

    if (hits.length() > 0) { System.out.println("Results: "); }

    for (int i = 0; i < hits.length(); i++) {
      Document doc = hits.doc(i);
      System.out.println((i+1) + ". " + doc.get("title") + " - " + doc.get("text") + ")");
    }

    is.close();

	} catch (Exception e) {
		System.out.println("Exception Caught....");
	}
  }


 




  public static void main (String[] args) {

  if (args.length < 2) {
    System.out.println("java AdsoIndexer [index/search] [file/searchterm] [searchfield]");
    return; 
  }

  String userCommand = ""; 
  String dataFile = "";
  String searchTerm = "";
  String searchField = "";



  if (args.length > 0) {
    userCommand = args[0];
  }
  if (args.length > 1) {
    dataFile = args[1];
    searchTerm = args[1];
  }
  if (args.length > 2) {
    searchField = args[2];
  }


  AdsoIndexer artin = new AdsoIndexer();


  if (userCommand.equals("index")) {
    try {
      artin.indexFile(dataFile);
    } catch (Exception e) {
      System.out.println("Error thrown while indexing document....");
    }
  } 

  if (userCommand.equals("search")) {
    if (searchTerm != "") { artin.searchTerm = searchTerm; }
    if (searchField != "") { artin.searchField = searchField; }
    artin.searchIndex();
  }

}







}



