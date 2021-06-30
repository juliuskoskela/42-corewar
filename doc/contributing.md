# Contributing

## Contexts

Contexts are reflected as github projects. The contexts are as follows:

Corewar - Research
Corewar - Implementation
Corewar - Validation


## Branches

```

master // Merge requires 100% test coverage, only accept pull request from dev.
dev // Merge requires compilation, accept any pull request. 
feature // Feature branch gets assigned.
feature_name // Personal fork if multiple assignees in a feature.

```

## Issues

- Issues can be assigned to one or multiple people.
- Issues can be drafted as cards.
- All issues must have a tag.
- Corewar - Rsearch project only accepts the tag `research`.
- Corewar - Implementation project only accepts tags `feature` and `bug`.

Tags:

```

feature
bug
research
documentation

```

Commands:

Detail command line commands required to work with issues.

## Pull Request

When merging to master you need to check the following things:

- Implementation tests 100% passed.
- Relevant documentation is updated, both README and SRS.
- Passes norminette v3 - beta.
- Passes valgrind, leaks or fsanitize. No leaks, no invalid reads or writes.
- Compiles with flags -Wall -Wextra -Werror
- Doesn't contain invalid functions.

A pull request should provide the following information when opened:

- An overview of proposed changes.
- Reasoning behind decisions.
- Possible benchmarks and test results.
- Possible links to resources.

## Commits

Commit messages should be descriptive. Try to commit only files that share a
context and don't mix multiple separate improvements in the same commit.
