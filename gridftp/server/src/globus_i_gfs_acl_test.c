/*
 *  user functions.  used by control.c or DSI implementation if it choses.
 */
#include "globus_i_gridftp_server.h"
#include "globus_gsi_authz.h"
#include "globus_i_gfs_acl.h"

#define GlobusACLTestFailure()                                              \
    globus_error_put(                                                       \
    globus_error_construct_error(                                           \
        GLOBUS_NULL,                                                        \
        GLOBUS_NULL,                                                        \
        GLOBUS_GFS_ERROR_MEMORY,                                            \
        __FILE__,                                                           \
        _gfs_name,                                                          \
        __LINE__,                                                           \
        "acl failed"))


static
int
globus_gfs_acl_test_init(
    void **                             out_handle,
    const struct passwd *               passwd,
    const char *                        given_pw,
    const char *                        resource_id,
    globus_i_gfs_acl_handle_t *         acl_handle,
    globus_result_t *                   out_res)
{
    char *                              fail_str;
    GlobusGFSName(globus_gfs_acl_test_init);

    fail_str = globus_libc_getenv("GLOBUS_GFS_ACL_TEST_FAIL");
    if(fail_str != NULL && (strcmp(fail_str, "ALL") == 0 || 
        strcmp(fail_str, "init") == 0))
    {
        *out_res = GlobusACLTestFailure();
    }
    else
    {
        *out_res = GLOBUS_SUCCESS;
    }
    if(globus_libc_getenv("GLOBUS_GFS_ACL_TEST_BLOCK"))
    {
        globus_gfs_acl_authorized_finished(acl_handle, *out_res);
        return GLOBUS_GFS_ACL_WOULD_BLOCK;
    }
    else
    {
        return GLOBUS_GFS_ACL_COMPLETE;
    }
}

static
int
globus_gfs_acl_test_authorize(
    void *                              out_handle,
    const char *                        action,
    const char *                        object,
    globus_i_gfs_acl_handle_t *         acl_handle,
    globus_result_t *                   out_res)
{
    char *                              fail_str;
    GlobusGFSName(globus_gfs_acl_test_authorize);

    fail_str = globus_libc_getenv("GLOBUS_GFS_ACL_TEST_FAIL");
    if(fail_str != NULL && (strcmp(fail_str, "ALL") == 0 || 
        strcmp(fail_str, action) == 0))
    {
        *out_res = GlobusACLTestFailure();
    }
    else
    {
        *out_res = GLOBUS_SUCCESS;
    }

    if(globus_libc_getenv("GLOBUS_GFS_ACL_TEST_BLOCK"))
    {
        globus_gfs_acl_authorized_finished(acl_handle, *out_res);
        return GLOBUS_GFS_ACL_WOULD_BLOCK;
    }
    else
    {
        return GLOBUS_GFS_ACL_COMPLETE;
    }
}


static void
globus_gfs_acl_test_destroy(
    void *                              out_handle)
{
}

globus_gfs_acl_module_t                 globus_gfs_acl_test_module = 
{
    globus_gfs_acl_test_init,
    globus_gfs_acl_test_authorize,
    globus_gfs_acl_test_destroy
};

