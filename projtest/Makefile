All: project.ps project.pdf

thesis.ps: thesis.tex tamuccthesis.cls tamuccthesis.sty
	latex thesis; bibtex thesis; latex thesis;
	dvips -o thesis.ps -t letter thesis.dvi  

# The following will create a postscript file of your project
#    Under linux you can view this with gv
# Notice that latex is called numerous times.  That is a sideeffect of using 
# bibtex, which creates the .bbl and .blg files, but then latex has to be run
# again to process those.  If you add a new cite, you will get [?] since latex
# just added it.  So a second call to latex after the bibtex normally fixes that
#
# If you project file gets rather large, you can remove the extra calls to latex
# and just remember that your bib might be off at any given time. When you are
# producing the final version do the extra executions of latex and bibtex. 
project.ps: project.tex COSCMSproject.cls COSCMSproject.sty
	latex project; bibtex project; latex project; latex project; 
	dvips -o project.ps -t letter project.dvi  

# If you fonts are coming out weird use the cmz printer with dvips
#	dvips -P cmz -t letter -o project.ps project.dvi

# Now we want a pdf of the project

project.pdf: project.ps
	ps2pdf project.ps project.pdf

# Sometimes the pdf files come out with bitmapped fonts instead of truetype 
#
# The following arguments have worked in the past to get better results
#         ps2pdf14 -dMaxSubsetPct=100\
               -dSubsetFonts=true -dEmbedAllFonts=true\
               -dAutoFilterColorImages=false -dAutoFilterGrayImages=false\
               project.ps project.pdf

