'use strict';

/**
 * @ngdoc service
 * @name clientApp.itemVariants
 * @description
 * # itemVariants
 * Service in the clientApp.
 */
angular.module('clientApp')
  .service('ItemVariants', function ($q, $http, $timeout, Config, $rootScope) {


    var ItemVariants = this;

    // A private cache key.
    var cache = {};

    /**
     * Return the promise with the items list, from cache or the server.
     *
     * @returns {*}
     */
    this.get = function(itemId) {
      // @todo: Add cache based on itemId.
      return getDataFromBackend(itemId);
    };

    /**
     * Return items array from the server.
     *
     * @returns {$q.promise}
     */
    function getDataFromBackend(itemId) {
      var deferred = $q.defer();
      var url = Config.backend + '/api/item_variants';
      var params = !!itemId ? {item: itemId} : {};

      $http({
        method: 'GET',
        url: url,
        params: params
      }).success(function(response) {
        setCache(response.data);
        deferred.resolve(response.data);
      });

      return deferred.promise;
    }

    /**
     * Save meters in cache, and broadcast en event to inform that the meters data changed.
     *
     * @param meters
     */
    var setCache = function(data) {
      // Cache data.
      cache = {
        data: data,
        timestamp: new Date()
      };

      // Clear cache in 60 seconds.
      $timeout(function() {
        cache.data = undefined;
      }, 60000);

      // Broadcast a change event.
      $rootScope.$broadcast('gb.item_variants.changed');
    }

  });
