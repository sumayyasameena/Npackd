#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "qfile.h"
#include "qlist.h"
#include "qurl.h"
#include "qtemporaryfile.h"
#include "qdom.h"

#include "package.h"
#include "packageversion.h"

/**
 * A repository is a list of packages and package versions.
 */
class Repository
{
private:
    // TODO: this is never freed
    static Repository* def;

    static Package* createPackage(QDomElement* e);
public:
    /**
     * Package versions.
     * TODO: does this leak memory?
     */
    QList<PackageVersion*> packageVersions;

    /**
     * Packages.
     * TODO: does this leak memory?
     */
    QList<Package*> packages;

    /**
     * Creates an empty repository.
     */
    Repository();

    /**
     * Loads the content from the URL.
     *
     * @param job job for this method
     */
    void load(Job* job);

    /**
     * Searches for a package by name.
     *
     * @param name name of the package like "org.server.Word"
     * @return found package or 0
     */
    Package* findPackage(QString& name);

    /**
     * @return newly created object pointing to the repository or 0
     */
    static QUrl* getRepositoryURL();

    /*
     * Changes the default repository url.
     *
     * @param url new URL
     */
    static void setRepositoryURL(QUrl& url);

    /**
     * @return default repository
     */
    static Repository* getDefault();
};

#endif // REPOSITORY_H
