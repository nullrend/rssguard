# (WIP!!!) ToC
* [Downloads](#downloads)
* [Foreword](#foreword)
* [Philosophy](#philosophy)
* [Versioning](#versioning)
* [Reporting bugs](#reporting-bugs)
* [Localizations](#localizations)
* [Web-based and lite app variants](#web-based-and-lite-app-variants)
* [Features](#features)
    * [List of main features](#list-of-main-features)
    * [Supported feed formats and online feed services](#supported-feed-formats-and-online-feed-services)
    * [Message filtering](#message-filtering)
    * [Database backends](#database-backends)
    * [Gmail](#gmail)
    * [Adblocking](#adblock)
* [Miscelaneous](#misc)
    * [Cleaning database](#cleaning-database)
    * [Portable user data](#portable-user-data)
    * [Downloading new messages](#downloading-new-messages)
    * [Generating debug log file](#generating-debug-log-file)

<img src="images/rssguard.png" width="64px">

# Downloads

- [Stable Releases](https://github.com/martinrotter/rssguard/releases)
- Development builds:
    - [Windows](https://bintray.com/martinrotter/rssguard/Development/Windows#files)
    - [Linux and MacOS](https://bintray.com/martinrotter/rssguard/Development/LinuxMacOs#files)

# Foreword
First, let me say, that you can contact RSS Guard's lead developer via [e-mail](mailto:rotter.martinos@gmail.com) or just submit a ticket here in the repository.

I am glad to accept any kind of donations, see ♥ **Sponsor** button on the top of this page. **I say "thank you" for all your support, my donators.** Also, I personally send "thank you" to all contributors (translators, source code contributors, issue reporters) and users.

## Philosophy
RSS Guard tends to be independent software. It's free, it's open-source. RSS Guard accepts donations but only as a way of saying "thank you for RSS Guard".

## Versioning
RSS Guard uses [semantic versioning](https://semver.org/). The versioning scheme is `X.Y.Z`, where:

* `X` marks major release version. This number will change very rarely and indicates critical new changes breaking backward compatibility.
* `Y` indicates that there is new major feature available.
* `Z` indicates that there are newly fixed bugs or small features introduced.

## Reporting bugs
Please report all issues/bugs/ideas to [Issues](https://github.com/martinrotter/rssguard/issues) section. Describe your problem as precisely as possible, along with steps taken leading up to the issue occurring.

It is a good idea to read [this](http://www.chiark.greenend.org.uk/~sgtatham/bugs.html) before reporting the bug; it will save time and effort for everyone if all the required information is provided from the get-go.

## Localizations
RSS Guard currently includes [many localizations](http://www.transifex.com/projects/p/rssguard).

If you are interested in creating translations for RSS Guard, then do this:

1. Go [here](http://www.transifex.com/projects/p/rssguard) and check status of currently supported localizations.
2. [Login](http://www.transifex.com/signin) (you can use social networks to login) and work on existing translations. If no translation team for your country/language exists, then ask for creating of localization team via the website.

**All translators commit themselves to keep their translations up-to-date. If some translations are not updated by their authors regularly and only small number of strings is translated, then those translations along with their teams will be eventually REMOVED from the project!!! At least 50% of strings must be translated for translation to being added to project.**

## Web-based and lite app variants
RSS Guard is distributed in two variants:

### Standard package with WebEngine-based bundled message viewer

This variant displays messages with their full formatting and layout in embedded Chromium-based web viewer. This variant of RSS Guard should be nice for everyone who doesn't care about memory consumption (RAM usage under Windows 10 rarely exceeds 100 MB however). Also, installation packages are relatively big.

<img src="images/webengine-view.png" width="80%">

### Lite package with simple text-based message viewer

This variant displays message in a much simpler and more lightweight text-based format. Layout and formatting of displayed message is simplified with no external web viewers are used; This results in a much smaller installation packages, much smaller memory footprint, and increased privacy of the user as many web resources are not downloaded by default like pictures, JavaScript and so on.

This variant of RSS Guard is meant for advanced users and can faster GUI response in some use-cases.

<img src="images/nonwebengine-view.png" width="80%">

If you're not sure which version to use, **use the Standard WebEngine package**. Download links for stable releases are available [here](https://github.com/martinrotter/rssguard/releases). If you wish to use a development build you can find [Windows](https://bintray.com/martinrotter/rssguard/Development/Windows#files) and [Linux/MacOS](https://bintray.com/martinrotter/rssguard/Development/LinuxMacOs#files) downloads available.

# Features
RSS Guard is simple (yet powerful) feed reader. It is able to fetch the most known feed formats, including RSS/RDF/ATOM/JSON. RSS Guard is developed on top of the [Qt library](http://qt-project.org) and it supports these operating systems:

* Windows Vista and newer,
* GNU/Linux,
* Mac OS X,
* Android (buildable and running).

## List of main features
* **Support for online feed synchronization via plugins**,
    * Tiny Tiny RSS (RSS Guard 3.0.0+)
    * Nextcloud News (RSS Guard 3.1.0+)
    * Inoreader (RSS Guard 3.5.0+)
    * Gmail with e-mail sending (RSS Guard 3.7.1+)
* Core:
    * Support for all feed formats (RSS/RDF/ATOM/JSON),
    * Full support of podcasts (RSS/ATOM/JSON),
    * Import/export of feeds to/from OPML 2.0,
    * Possibility of using custom 3rd-party feed synchronization services,
    * Feed metadata fetching including icons,
    * Simple internal Chromium-based web viewer (or alternative version with simpler and much more lightweight internal viewer),
    * Scriptable [message filtering](#message-filtering),
    * Downloader with own tab and support for up to 6 parallel downloads,
    * Ability to cleanup internal message database with various options,
    * Enhanced feed auto-updating with separate time intervals,
    * "Portable" mode support with clever auto-detection,
    * Feed categorization,
    * Feed authentication (BASIC),
    * Handles tons of messages & feeds,
    * Ability to backup/restore database or settings,
    * Fully-featured recycle bin,
    * Multiple data backend support,
        * SQLite (in-memory DBs too),
        * MySQL.
    * Ability to specify target database by its name (MySQL backend),
    * Support for `feed://` URI scheme.
* User interface:
    * Message list filter with regular expressions,
    * Drag-n-drop for feed list,
    * Able to show unread feeds/messages only,
    * Can be controlled via keyboard,
    * Fully adjustable toolbars (changeable buttons and style),
    * Hideable main menu, toolbars and list headers,
    * Bundled icon themes (Numix & Papirus),
    * Fully skinnable user interface + ability to create your own skins,
    * Newspaper view,
    * Tabbed interface,
    * Ability to hide list of feeds/categories,
    * Desktop integration via tray icon,
    * Localizations to some languages,
    * Ability to tweak columns in displayed list of messages.

## Supported feed formats and online feed services
RSS Guard is a modular application which supports plugins. It offers well-maintained and relatively stable [plugin API](https://github.com/martinrotter/rssguard/blob/master/src/librssguard/services/abstract/serviceentrypoint.h) which can be used to add support for various online feed services, extend a way feeds are processed or add totally new functionality to RSS Guard. At this point RSS Guard offers these plugins which are bundled in all installation packages and some of their features are described in detail in this documentation:
* Standard `RSS/RDF/ATOM/JSON` plugin: This is the core plugin of RSS Guard which allows you to user the app like normal standalone feed reader with great features everyone would expect, including `OPML` files export and import or feed metadata fetching. Also podcasts are supported.
* [Tiny Tiny RSS](https://tt-rss.org) plugin: Adds ability to synchronize messages with TT-RSS instances, either self-hosted or via 3rd-party external service.
* [Inoreader](https://www.inoreader.com) plugin: Adds ability to synchronize messages with Inoreader. All you need to do is create free account on their website and start rocking.
* [Nextcloud News](https://apps.nextcloud.com/apps/news) plugin: Nextcloud News is a Nextcloud app which adds feed reader abilities into your Nextcloud instances.
* [Gmail](https://www.google.com/gmail) plugin: Yes, you are reading it right. RSS Guard can be used as very lightweight and simple e-mail client. This plugins uses [Gmail API](https://developers.google.com/gmail/api) and offers even e-mail sending.

All plugins share almost all core RSS Guard's features, including labels, recycle bins, podcasts fetching or newspaper view. They are implemented in a very transparent way, making it easy to maintain them or add new ones. For more information on how to configure them please refer to the [Accounts](accounts.md) help document.

Usually, plugins have some exclusive functionality, for example Gmail plugin allows user to send e-mail messages. This extra functionality is always accessible via plugin's context menu and also via main menu.

<img src="images/gmail-context-menu.png" width="80%">

If there is interest in other plugins, you might write one yourself or if many people are interested then I might write it for you, even commercially if we make proper arrangements.

### Features found exclusively in `standard RSS` plugin
Standard plugin in RSS Guard offers some features which are specific to it. Of course it supports all news syndication formats which are nowadays used:
* RSS 0.90, 0.91, 0.92, 1.0 (also know as *RDF*), 2.0.
* ATOM 1.0,
* [JSON](https://www.jsonfeed.org).

Standard plugin offers some extra features like export/import of OPML 2.0 files or fetching feed metadata:

### Import and export feeds

RSS Guard supports [OPML](https://en.wikipedia.org/wiki/OPML) files as its standard method of importing and exporting feeds.

#### Import feeds

1. Add a new [account](accounts.md) if one does not exist already.
2. Go to **Accounts** and select the desired account. You can also right-click the account in the Feed List pane and select **Import feeds**.
3. Click **Select file** to open a file browser window and navigate to your OPML file.
4. You will be given the option to fetch all feed metadata. Depending on how many feeds are being imported and the number of messages in each feed the process might take some time. Network bandwidth and latency also have an effect on this process.
4. The **Root node** refers to the category the feeds will be imported into in the event you have already created one for the current account— in this case "category" is synoymous with a _folder_.
5. You can select which feeds to import or leave out from the process.
6. Click **Import from file** to finish the process. Should there be any errors a message will appear.

#### Export feeds

1. Go to **Accounts** and select the desired account. You can also right-click the account in the Feed List pane and select **Export feeds**.
2. Click **Select file** to open a file browser window and select a location and name for the OPML file to be created.
3. Select which feeds to export
4. Click **Export to file** to finish the process. Should there be any errors a message will appear.

## Message filtering
RSS Guard supports _automagic_ message filtering. The filtering system is automatically triggered when new messages for each feed are downloaded. User can write scripts which perform filtering decisions. [**JavaScript with ECMA standard**](http://www.ecma-international.org/publications/standards/Ecma-262.htm) is supported.

For more detailed information please refer to the [message filtering document](message-filter.md).

### Performance
Note that evaluations of JavaScript expressions are NOT that fast. They are much slower than native `C++` code, but well-optimized scripts usually take only several milliseconds to finish for each message.

## Database backends
RSS Guard offers switchable database backends which hold your data. At this point, two backends are available:
* MariaDB,
* SQLite (default).

SQLite backend is the default database engine used and configuration is needed to use it. It storeds all data in a single file (Check `About RSS Guard → Resources` to find its location). 

MariaDB (MySQL) backend is there for users who want to store their data in a centralized way or require more power for the organization and storage of of hundreds of feeds. You can use a single server across separate RSS Guard instances on multiple systems.

For more information please refer to the [database backends](database-backends.md) document.

## Gmail
RSS Guard includes Gmail plugin, which allows users to receive and send (!!!) e-mail messages. Plugin uses [Gmail API](https://developers.google.com/gmail/api) and offers some e-mail client-like features:
* Sending e-mail messages.

<img src="images/gmail-new-email.png">

* You can also reply to existing messages.
* Plugin is able to suggest recipient's e-mail.

## Adblocking
Support for filtering rules based on [Adblock Plus](https://adblockplus.org/) is supported! Find more information in [adblocking](adblock.md).

# Miscelaneous
Here you can find some useful insights into RSS Guard's modus operandi.

## Cleaning database
Your RSS Guard's database can grow really big over time, therefore you might need to do its cleanup regularly. There is a dialog `Cleanup database` in `Tools` menu to do just that for you, but note that RSS Guard should run just fine even with thousands of messages.

## Portable user data
RSS Guard checks "config directory" (this is `C:\Users\<user>\AppData\Local` directory on Windows) for existence of file:
```
RSS Guard\data\config\config.ini
```
If that file exists, then RSS Guard will use the file (this is called _non-portable **FALLBACK** settings_). If this file is not found, then application will check if its root path (folder, in which RSS Guard executable is installed) is writable, and if it is, it will store settings in it, in subfolder:
```
data\config\config.ini
```
This is _fully-portable mode_. Check `About RSS Guard -> Resources` dialog to find more info on significant paths used.

## Downloading new messages
Here is the rough workflow which is done when you hit `Feeds & categories -> Update all items` or `Feeds & categories -> Update selected items`. At that point of time this happens:
1. RSS Guard creates a list of all/selected feeds.
2. Sequentially, for each feed do:
    * a. Download all available messages from online source.
    * b. Sequentially, for each message do:
        * 1. Sanitize title of the message. This includes replacing all non-breaking spaces with normal spaces, removing all leading spaces, replacing all multiple consecutive spaces with single space. Contents of message are converted from [percent-encoding](https://en.wikipedia.org/wiki/Percent-encoding).
        * 2. Run all [message filters](#message-filtering), one by one, one the message. Cache read/important message attributes changed by filters to queue which is later synchronized back to online feed service.
        * 3. Store the message into RSS Guard's database, creating completely new DB entry for it, or replacing existing message. **Note that two messages are considered as the same message if they have identical URL, author and title and they belong to the same feed.** This does not stand for synchronized feeds (TT-RSS, Inoreader and others) where each message has assigned special ID which identifies the message.

## Generating debug log file
If you run into problems with RSS Guard and you need your problems fixed, you should provide log file from the time when problem occurred. RSS Guard writes all important information to standard output, which is usually calling terminal.

To redirect debug output of RSS Guard to log file, do this:

* Windows
  1. Open a command prompt by pressing <key>Win</key> + <key>R</key>, then typing `cmd`.
  2. Navigate to your RSS Guard installation folder. If RSS Guard was installed the default path is `C:\Programs\rssguard\`. This is the folder which contains `rssguard.exe`.
  3. Enter `.\rssguard.exe --log '.\log.txt'`. RSS Guard will now start. You can of course specify arbitrary file where to store log and its location must be writable. The `--log` syntax is supported starting from RSS Guard 3.8.0. Older versions do not support capturing debug output.
  4. Now try to simulate your problem.
  5. Attach generated `log.txt` file to your bug report.

* Linux
  1. You need to open command line, run terminal emulator.
  2. Navigate to your RSS Guard installation folder, `cd /my/root/rssguard`. This step is not usually needed.
  3. Enter `rssguard > /home/<user>/log.txt 2>&1`. RSS Guard will now start.
  4. Now try to simulate your problem.
  5. Attach generated `log.txt` file to your bug report.
