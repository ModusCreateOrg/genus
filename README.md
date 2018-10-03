# Modus Create's Genus Holiday Game

[![Modus Create](./images/modus.logo.svg)](https://moduscreate.com)

[![Build Status](https://ci.moduscreate.com/buildStatus/icon?job=ModusCreateOrg/genus/master&build=1)](https://ci.moduscreate.com/job/ModusCreateOrg/job/genus/job/master/1/)

## Repository set up for development

This repo and the creative-engine repo work together.  A soft link to creative-engine is automatically created by cmake or make.

Thus you will need to fork and clone this and the creative-engine repos AT THE SAME LEVEL:

```
$ ls ~/github
genus/  creative-engine/
```

In genus/ you will need to create a soft link"
```
$ cd genus
$ ln -s ../creative-engine .
```

## Git Workflow
Read about [GitHub workflow](https://github.com/ModusCreateOrg/creative-engine) at the creative-engine repo.

The gist is that we fork the main repos and work in our private forks.  We push to our forks.  We create Pull Requests against the main repos.

The only way code makes it into master in the main repo is if we merge a PR.

# ModusCreateOrg GitHub Guidelines

> Modus Create team members should refer to [ModusCreateOrg GitHub Guidelines](https://docs.google.com/document/d/1eBFta4gP3-eZ4Gcpx0ww9SHAH6GrOoPSLmTFZ7R8foo/edit#heading=h.sjyqpqnsjmjl)


