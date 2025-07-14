function TryCommand {
    param(
        [Parameter(
            Mandatory=$True,
            Position = 0
        )]
        [string] 
        $command,
        [Parameter(
            Mandatory=$False,
            ValueFromRemainingArguments=$True,
            Position = 1
        )]
        [string[]]
        $extraargs,
        [Alias("Log")]
        [switch]$write_output
    )
    try {
        $fullcommand = @($command) + $extraargs
        if (Get-Command -ArgumentList $fullcommand){
            if ($write_output){
                Write-Output('"' + ($fullcommand -join " ") + '" is valid')
            }
            return $True
        }
    }
    catch {
        if ($write_output){
            Write-Output("Can't find command " + ($fullcommand -join " "))
        }
        return $False
    }
    return $False
}

# Seek python
$has_python = TryCommand python
if ($has_python -eq $False){
    Write-Output('Warning: Command "python" was not found, exiting...')
    exit 1
} else {
    Write-Output('"python" is present!')
}

# Run existence check.
& python ./py_buildutils/module_existence.py pybind11
if ($LASTEXITCODE -eq 1){
    Write-Output('Pybind11 dependency could not be resolved.')
    exit 1
} else {
    Write-Output("Pybind11 module found!")
}

& python ./py_buildutils/minimum_version.py 3.7
if ($LASTEXITCODE -eq 1){
    Write-Output('Unexpected error occured while checking python version.')
    exit 1
} elseif ($LASTEXITCODE -eq 2) {
    Write-Output("Python version isn't compatible, consider using a tool like 'pyenv' to set a compatible version.")
    exit 1
}

$Env:FOUND_PYTHON_PATH = & python ./py_buildutils/pyfolder.py
Write-Output("Found Python at: " + $Env:FOUND_PYTHON_PATH)
$Env:FOUND_PYBIND11_PATH = & python ./py_buildutils/pybind11folder.py
Write-Output("Found pybind11 at: " + $Env:FOUND_PYBIND11_PATH)
$Env:FOUND_PYBIND11_CMAKE_PATH = & python ./py_buildutils/pybind11folder_cmake.py
Write-Output("Found pybind11 cmake at: " + $Env:FOUND_PYBIND11_CMAKE_PATH)

cmake -S . -B ./build
cmake --build ./build 