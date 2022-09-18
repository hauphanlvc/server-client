# Tutorial: https://kubernetes.io/docs/tasks/configure-pod-container/pull-image-private-registry/

## To create secret docker registry
```
kubectl create secret generic intern-registry --from-file=.dockerconfigjson=$HOME/.docker/config.json --type=kubernetes.io/dockerconfigjson -n soldiers-ext
```
## To show secret intern-registry
```
kubectl -n soldiers-ext get secret intern-registry --output=yaml
``