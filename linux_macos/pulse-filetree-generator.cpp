#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <list>
#include <set>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <linux/limits.h>
#include <sys/stat.h>


using namespace std;

 ///g++  -O3 pulse-filetree-generator.cpp -o pulse-filetree-generator

static
  std::string &
ltrim (std::string & s);
static
  std::string &
rtrim (std::string & s);
static
  std::string &
trim (std::string & s);
std::vector < std::string > split (const std::string & s, char delimiter);
bool
dir_exist (char *path);

struct section
{
  std::string
    name;
  std::unordered_map <
    std::string,
    std::string >
    keyvalues;
};
//________________________________________________________________
//___________________Parse init file _____________________________
//________________________________________________________________
class
  config
{
public:
  config (const std::string & filename);

  section *
  get_section (const std::string & sectionname);
  std::list <
  section > &
  get_sections ();

  std::string
  get_value (const std::string & sectionname, const std::string & keyname);

private:
  void
  parse (const std::string & filename);

  std::list <
    section >
    sections;
};

config::config (const std::string & filename)
{
  parse (filename);
}

section *
config::get_section (const std::string & sectionname)
{
  std::list < section >::iterator found =
    std::find_if (sections.begin (), sections.end (),
		  [sectionname] (const section & sect)
		  {
		  return sect.name.compare (sectionname) == 0;
		  }
  );

  return found != sections.end ()? &*found : NULL;
}

std::list < section > &config::get_sections ()
{
  return sections;
}

std::string config::get_value (const std::string & sectionname,
			       const std::string & keyname)
{
  section *
    sect = get_section (sectionname);
  if (sect != NULL)
    {
      std::unordered_map < std::string, std::string >::const_iterator it =
	sect->keyvalues.find (keyname);
      if (it != sect->keyvalues.end ())
	return it->second;
    }
  return "";
}

void
config::parse (const std::string & filename)
{
  section currentsection;
  std::ifstream fstrm;
  fstrm.open (filename);

  if (!fstrm)
    throw std::invalid_argument (filename + " could not be opened");

  for (std::string line; std::getline (fstrm, line);)
    {
      // if a comment
      if (!line.empty () && (line[0] == ';' || line[0] == '#'))
	{
	  // allow both ; and # comments at the start of a line

	}
      else if (line[0] == '[')
	{
	  /* A "[section]" line */
	  size_t end = line.find_first_of (']');
	  if (end != std::string::npos)
	    {

	      // this is a new section so if we have a current section populated, add it to list
	      if (!currentsection.name.empty ())
		{
		  sections.push_back (currentsection);	// copy
		  currentsection.name.clear ();	// clear section for re-use
		  currentsection.keyvalues.clear ();
		}
	      currentsection.name = line.substr (1, end - 1);
	    }
	  else
	    {
	      // section has no closing ] char
	    }
	}
      else if (!line.empty ())
	{
	  /* Not a comment, must be a name[=:]value pair */
	  size_t end = line.find_first_of ("=:");
	  if (end != std::string::npos)
	    {
	      std::string name = line.substr (0, end);
	      std::string value = line.substr (end + 1);
	      ltrim (rtrim (name));
	      ltrim (rtrim (value));

	      currentsection.keyvalues[name] = value;

	    }
	  else
	    {
	      // no key value delimitter
	    }
	}
    }				// for


  // if we are out of loop we add last section
  // this is a new section so if we have a current section populated, add it to list
  if (!currentsection.name.empty ())
    {
      sections.push_back (currentsection);	// copy
      currentsection.name = "";
      currentsection.keyvalues.clear ();
    }
}

//________________________________________________________________
//________________________________________________________________
//________________________________________________________________

//________________________________________________________________
//_______________________utils Function___________________________
//________________________________________________________________
// trim leading white-spaces
static
  std::string &
ltrim (std::string & s)
{
  size_t startpos = s.find_first_not_of (" \t\r\n\v\f");
  if (std::string::npos != startpos)
    {
      s = s.substr (startpos);
    }
  return s;
}

// trim trailing white-spaces
static
  std::string &
rtrim (std::string & s)
{
  size_t endpos = s.find_last_not_of (" \t\r\n\v\f");
  if (std::string::npos != endpos)
    {
      s = s.substr (0, endpos + 1);
    }
  return s;
}

static
  std::string &
trim (std::string & s)
{
  return rtrim (ltrim (s));
}

std::vector < std::string > split (const std::string & s, char delimiter)
{
  std::vector < std::string > tokens;
  std::string token;
  std::istringstream tokenStream (s);
  while (std::getline (tokenStream, token, delimiter))
    {
      tokens.push_back (token);
    }
  return tokens;
}

template < typename Type > void
display (Type & v)
{
  typename
    Type::iterator
    it;
  for (it = v.begin (); it != v.end (); ++it)
    {
      std::cout << *it << std::endl;
    }
}

bool
dir_exist (char *path)
{
  struct stat
    st;
  if (stat (path, &st) == 0)
    if (st.st_mode & S_IFDIR != 0)
      return true;
  return false;
}

int
file_exist (const char *name)
{
  struct stat
    st;
  return (stat (name, &st) == 0);
}

//________________________________________________________________
//________________________________________________________________
//________________________________________________________________

//________________________________________________________________
//____________________Creation json tree__________________________
//________________________________________________________________

//void listdir(const char *name, int indent, FILE * fp, string& result)
void
listdir (const char *name, FILE *fp, std::set < std::string > &parts)
{
  DIR *
    dir;
  struct dirent *
    entry;
  char
    espacea[5] = " {";
  char
    namefile[2024];
  string
    path;
  if (!(dir = opendir (name)))
    return;
  while ((entry = readdir (dir)) != NULL)
    {
      if (entry->d_type == DT_DIR)
	{
	  // folders 
	  if (strcmp (entry->d_name, ".") == 0
	      || strcmp (entry->d_name, "..") == 0)
	    // pass name file  ".." et "." file
	    continue;
	  // create absolue name directory
	  path = string (name) + "/" + string (entry->d_name);
	  if (path.rfind ("//", 0) == 0)
	    {
	      path.erase (0, 1);
	    }
	  // prepare ecriture file.
	  snprintf (namefile, sizeof (namefile),
		    "%s\"text\" : \"%s\", \"children\" : [", espacea,
		    entry->d_name);
	  fprintf (fp, "%s\"text\" : \"%s\", \"children\" : [", espacea,
		   entry->d_name);
	  strcpy (espacea, ",{");
	  std::set < std::string >::iterator it = parts.find (path);
	  const bool
	    is_in = (it != parts.end ());
	  if (it != parts.end ())
	    {
	      // on supprime de la liste des exclusions
	      parts.erase (it);
	    }
	  if (!is_in)
	    {
	      listdir (path.c_str (), fp, parts);
	    }
	  fprintf (fp, "]}");
	}
    }
  closedir (dir);
}

//________________________________________________________________
//_____________________lit option line de command_________________
//________________________________________________________________

char *
getCmdOption (char **begin, char **end, const std::string & option)
{
  char **
    itr = std::find (begin, end, option);
  if (itr != end && ++itr != end)
    {
      return *itr;
    }
  return 0;
}

bool
cmdOptionExists (char **begin, char **end, const std::string & option)
{
  return std::find (begin, end, option) != end;
}

//________________________________________________________________
//________________________usage program________________________________
//________________________________________________________________

void
usage (int argc, char *argv[])
{
  cout << "Usage : " << endl;
  cout << "\tcommand :" << argv[0] << endl;
  cout << endl << "\tmandatory parameter :" << endl;
  cout << "\t\t -r \"root file system\"" << endl;
  cout << endl << "\toptional parameters :" << endl;
  cout <<
    "\t\t -f \"file configuration\"   /etc/pulse-xmpp-agent/agentconf.ini par default"
    << endl;
  cout << "\t\t -o \"file output\"          /tmp/file.txt par default" <<
    endl;
  cout << endl << "\tExample :" << endl;
  cout << "\t" << argv[0] <<
    " -r \"/\" -o \"/tmp/azerty.txt\" -f \"etc/pulse-xmpp-agent/agentconf.ini\""
    << endl;
  cout << endl;
  cout <<
    "\t definir listexclude dans fichier de configuration section browserfile"
    << endl;
  cout << "example :" << endl;
  cout << "[browserfile]" << endl;
  cout << "defaultdir = /tmp" << endl;
  cout << "rootfilesystem = /tmp" << endl;
  cout <<
    "listexclude = /usr, /lib,/boot,/cdrom,/dev,/lib32,/lib64,/lost+found,/media,/mnt,/opt,/partage,/proc,/root,/run,/sbin,/snap,/somewhere,/srv,/sys"
    << endl;
}

//________________________________________________________________
//________________________________________________________________
//________________________________________________________________
//result pas utilise, mais a utiliser si on veut le fichier genere dans une varaible. 
int
main (int argc, char *argv[])
{
  std::vector < std::string >::iterator it;
  std::set < std::string > parts;
  std::set < std::string >::iterator itset;

  char
    outfilename[PATH_MAX];
  char
    filename[PATH_MAX];

  char
    filenameconf[PATH_MAX];
  if (cmdOptionExists (argv, argv + argc, "-h") || argc == 1)
    {
      usage (argc, argv);
      return !(argc != 1);
    }

  strcpy (filenameconf, "/etc/pulse-xmpp-agent/agentconf.ini");
  char *
    filename1 = getCmdOption (argv, argv + argc, "-f");
  if (filename1)
    {
      strcpy (filenameconf, filename1);
    }
  else
    {
      cout << "configuration file is : " << filenameconf << endl;
    }

  char *
    rootfilesystem = getCmdOption (argv, argv + argc, "-r");
  if (!rootfilesystem)
    {
      cerr << "Error : root file system missing option -r \"rootfilesystem\""
	<< endl;
      usage (argc, argv);
      return -1;
    }

  if (!dir_exist (rootfilesystem))
    {
      cerr << "Error : folder " << rootfilesystem << " does not exist" <<
	endl;
      //fprintf(stderr, "error arg1 (%s) is not folder", rootfilesystem);
      return -1;
    }

  strcpy (outfilename, "/tmp/file.txt");
  char *
    outputfile = getCmdOption (argv, argv + argc, "-o");
  if (outputfile)
    {
      strcpy (outfilename, outputfile);
    }
  cout << "output file to : " << outfilename << endl;
  std::vector < std::string > dd;
  if (file_exist (filenameconf))
    {
      config
      cfg (filenameconf);
      section *
	usersection = cfg.get_section ("browserfile");
      if (usersection != NULL)
	{
//                 std::cout << "section name: " << usersection->name << std::endl;
//                 std::cout << "defaultdir=" << cfg.get_value("browserfile", "defaultdir") << '\n';
//                 std::cout << "rootfilesystem=" << cfg.get_value("browserfile", "rootfilesystem") << '\n';
	  std::cout << "exclusion list is " << cfg.get_value ("browserfile",
							      "listexclude")
	    << '\n';
	}
      dd = split (cfg.get_value ("browserfile", "listexclude"), ',');
    }
  else
    {
      cout << "not configuration file, listexclude is empty" << endl;
    }

  for (it = dd.begin (); it != dd.end (); ++it)
    {
      trim (*it);
    }
  //convertit en set
  set < string > sa (dd.begin (), dd.end ());
  //display(sa);
  string
    dede;
  FILE *
    fp;
  fp = fopen (outfilename, "w+");

  if (argv[1][0] == '/')
    {
      strcpy (filename, &argv[1][1]);
    }
  else
    {
      strcpy (filename, argv[1]);
    }
  fprintf (fp, "{ \"text\" : \"%s\", \"children\" : [", filename);
  listdir (rootfilesystem, fp, sa);
  fprintf (fp, "]}");
  fclose (fp);
  return 0;
}
