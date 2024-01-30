# Configuration Files

All configuration files utilized by the controller-manager are retrieved from S3 at the path `s3://bulk-provision/hulk-operator/`. If any file within this directory is modified locally, it is crucial to synchronize those changes with the corresponding files in S3.

## Commands

Update s3 with the latest local configs. **Note: Use with caution**
```sh
make configs-s3-upload
```

Download latest config from s3
```sh
make configs-s3-download
```
