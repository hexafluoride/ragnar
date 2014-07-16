# Ragnar
Ragnar is a C++/CLI wrapper for Rasterbar's *libtorrent*. It aims to provide a (mostly) complete interface to the underlying C++ library.

## Usage

### 1. Install the NuGet package.

```posh
PM> Install-Package Ragnar
```

### 2. Create a session

```csharp
using(var session = new Session())
{
    // Make the session listen on a port in the range
    // 6881-6889
    session.ListenOn(6881, 6889);

    // Create the AddTorrentParams with info about the torrent
    // we'd like to add.
    var addParams = new AddTorrentParams
    {
        SavePath = "C:\\Downloads",
        Url = "<url to a torrent file>"
    };

    // Add a torrent to the session and get a `TorrentHandle`
    // in return.
    var handle = session.AddTorrent(addParams);

    while(true)
    {
        // Get a `TorrentStatus` instance from the handle.
        var status = handle.QueryStatus();

        // If we are seeding, our job here is done.
        if(status.IsSeeding)
        {
            break;
        }

        // Print our progress and sleep for a bit.
        Console.WriteLine("{0}% downloaded", status.Progress * 100);
        Thread.Sleep(1000);
    }
}
```

## How to build from source
To build Ragnar from source, you will need the following sources and tools.

* [Boost (v1.55.0)](http://www.boost.org/users/history/version_1_55_0.html)
* [libtorrent (v1.0.0)](http://sourceforge.net/projects/libtorrent/files/libtorrent/)
* Visual Studio 2013 (MSVC 12.0)
* The environment variable `BOOST_ROOT` pointing to the Boost sources.
* The environment variable `LIBTORRENT` pointing to the libtorrent sources.

### 1. Building Boost
Download and unpack Boost. For the example, I will assume Boost lives at `C:\Code\boost_1_55_0`. Set the environment variable `BOOST_ROOT` to this directory.

In a command prompt, `cd` to `BOOST_ROOT` and run `bootstrap`. *Keep this command prompt open.*

When the bootstrapping process finishes, open `%BOOST_ROOT%\project-config.jam`. It should look something like this,

```
import option ; 
 
using msvc : 12.0 ; 
 
option.set keep-going : false ; 
```

The important part is the `using msvc : 12.0`. Make your changes and save the file.

In your command prompt, run `b2`. This will take a while. Have a coffee - when it's finished, proceed with step 2.

### 2. Building libtorrent
Download and unpack libtorrent. For the example, I will assume libtorrent lives at `C:\Code\libtorrent-rasterbar-1.0.0`. Set the environment variable `LIBTORRENT` to this directory.

Create the file `%LIBTORRENT%\build.bat` with the following contents, [credits](http://thomasfischer.biz/building-libtorrent-for-windows-with-visual-studio-2012/)

```
@echo on
set BOOST_BUILD_PATH=%BOOST_ROOT%
SET PATH=%PATH%;%BOOST_ROOT%
SET CL=/I%BOOST_ROOT%
bjam toolset=msvc-12.0 boost-link=static geoip=off encryption=tommath link=static variant=%1
@pause
```

In a command prompt, `cd %LIBTORRENT%` and run `build debug` followed by `build release`. This will build libtorrent as a static library in both debug and release configurations.

### 3. Building Ragnar
Open `Ragnar.sln` in Visual Studio 2013. Press `F6`. Wait a while. Success. If not - report an issue.

## Contributing
* Fork the repository.
* Make your feature addition or bug fix.
* Send a pull request. *Bonus for topic branches. Funny .gif will be your reward.*

## License
Copyright (c) 2014, Viktor Elofsson and contributors

Ragnar is provided as-is under the **MIT** license. For more information see `LICENSE`.

*For Boost, see http://svn.boost.org/svn/boost/trunk/LICENSE_1_0.txt*

*For libtorrent, see https://libtorrent.googlecode.com/svn/trunk/LICENSE*
